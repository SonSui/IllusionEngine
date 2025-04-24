#include "TileMapComponent.h"
#include "Actor.h"
#include "IMath.h"
#include "TextureSplitter.h"
#include <fstream>
#include <sstream>
#include <algorithm> // std::sort

// コンストラクター
// ここではSpriteComponentの初期化を行い、mRenderer等を設定する。
// タイル幅やタイル高さ、ビューポートも初期化する。
//TileMapComponent::TileMapComponent(Actor* owner, SDL_Renderer* renderer, int updateOrder)
//    : SpriteComponent(owner, updateOrder)
//    , mRenderer(renderer)
//    , mTileWidth(0.0f)
//    , mTileHeight(0.0f)
//    , mViewport{ 0.0f, 0.0f, 800.0f, 600.0f } // デフォルトのビューポート適当
//{
//    // SpriteComponent側でもレンダラーを使うなら、mOwner->GetGame()->AddSprite(this);
//    // はSpriteComponentのコンストラクターで既に呼んでいる。
//    // 必要に応じて他初期化
//}

// タイルシート設定
// タイル画像のテクスチャと各種パラメータをTextureSplitterにセットし、
// 分割済みテクスチャを利用できるようにする。
void TileMapComponent::SetTileSheet(
    SDL_Texture* tilesheet,
    float tileWidth,
    float tileHeight,
    float offsetX,
    float offsetY,
    float spacingX,
    float spacingY
)
{
    mTileWidth = tileWidth;
    mTileHeight = tileHeight;

    // TextureSplitterを利用してタイルを分割
    mTextureSplitter.SplitTexture(
        tilesheet,
        tileWidth,
        tileHeight,
        offsetX,
        offsetY,
        spacingX,
        spacingY
    );

    // 通常のSpriteComponent側のメンバにも分割テクスチャを設定しておく
    // （SpriteComponentの処理を活用したい場合などに備える）
    // ただしこれにより isSplitTexture = true となる
    SetTextureSplitter(&mTextureSplitter);
}

// CSVファイルからマップをロード
// 簡易的に、カンマ区切りの数値を行ごとに読み込み、2次元配列に格納する。
// 最終的にLoadMapを呼び出してマップをセットする。
bool TileMapComponent::LoadMapFromCSV(const std::string& filename)
{
    std::ifstream ifs(filename);
    if (!ifs.is_open())
    {
        SDL_Log("Failed to open CSV file: %s", filename.c_str());
        return false;
    }

    std::vector<std::vector<int>> mapData;
    std::string line;
    while (std::getline(ifs, line))
    {
        std::stringstream ss(line);
        std::string cell;
        std::vector<int> rowData;
        while (std::getline(ss, cell, ','))
        {
            // CSVのセルをintに変換
            int val = std::stoi(cell);
            rowData.push_back(val);
        }
        mapData.push_back(rowData);
    }
    ifs.close();

    return LoadMap(mapData);
}

// 2次元配列からマップをロード
// 今回は既存レイヤーをクリアして、新しい単一レイヤーを追加する実装とする。
// 「複数レイヤーをCSVからまとめて読みたい」場合は改造が必要。
bool TileMapComponent::LoadMap(const std::vector<std::vector<int>>& mapData)
{
    // 既存レイヤーをクリア
    mLayers.clear();

    // 単一レイヤーを追加
    if (mapData.empty())
    {
        SDL_Log("LoadMap: mapData is empty");
        return false;
    }
    AddLayer(mapData, 0, true, 1.0f);
    return true;
}

// レイヤーを追加
// 指定された2次元配列データをもとにLayer構造体を生成してmLayersに格納する。
// zOrderで描画順をコントロールし、visibleやopacityもセット。
void TileMapComponent::AddLayer(
    const std::vector<std::vector<int>>& layerData,
    int zOrder,
    bool visible,
    float opacity
)
{
    Layer layer;
    layer.data = layerData;
    layer.visible = visible;
    layer.opacity = opacity;
    layer.zOrder = zOrder;

    mLayers.push_back(layer);

    // レイヤー追加後、zOrderの昇順で並べ替えたい場合
    std::sort(mLayers.begin(), mLayers.end(), [](const Layer& a, const Layer& b) {
        return a.zOrder < b.zOrder;
        });
}

// 描画
// 可視レイヤーだけを描画。各タイルIDに応じたテクスチャの一部を描画する。
void TileMapComponent::Draw(SDL_Renderer* renderer)
{
    // ※ SpriteComponent::Draw() はSpriteとしての描画を行う実装だが、
    //   ここではTileMap用の描画に置き換えるために独自処理。

    for (auto& layer : mLayers)
    {
        if (!layer.visible || layer.opacity <= 0.0f)
        {
            // 可視じゃない or 不透明度0
            continue;
        }

        // タイルを一枚ずつ描画
        // 可視タイル範囲を求める
        SDL_FRect visibleRect = CalculateVisibleTiles();
        // タイル座標範囲を計算
        int minCol = static_cast<int>(visibleRect.x);
        int maxCol = static_cast<int>(visibleRect.x + visibleRect.w);
        int minRow = static_cast<int>(visibleRect.y);
        int maxRow = static_cast<int>(visibleRect.y + visibleRect.h);

        // レイヤーデータの行列サイズを取得
        int numRows = static_cast<int>(layer.data.size());
        int numCols = (numRows > 0) ? static_cast<int>(layer.data[0].size()) : 0;

        // alphaMod を設定（0～255）
        Uint8 oldAlpha = 255;
        SDL_GetTextureAlphaMod(mTextureSplitter.GetSourceTexture(), &oldAlpha);
        Uint8 newAlpha = static_cast<Uint8>(layer.opacity * 255.0f);
        SDL_SetTextureAlphaMod(mTextureSplitter.GetSourceTexture(), newAlpha);

        // タイル描画ループ
        for (int row = minRow; row < maxRow; ++row)
        {
            if (row < 0 || row >= numRows) continue;

            for (int col = minCol; col < maxCol; ++col)
            {
                if (col < 0 || col >= numCols) continue;

                int tileID = layer.data[row][col];
                if (tileID < 0 || tileID >= mTextureSplitter.GetTileCount())
                {
                    // 無効タイル
                    continue;
                }

                // タイルのソース領域を取得
                const SDL_FRect& srcRect = mTextureSplitter.GetTileRect(tileID);

                // タイルを表示するスクリーン座標を計算
                // ビューポートを考慮してオフセットさせる
                SDL_FRect dstRect;
                dstRect.x = col * mTileWidth - mViewport.x;
                dstRect.y = row * mTileHeight - mViewport.y;
                dstRect.w = mTileWidth;
                dstRect.h = mTileHeight;

                // オーナーのScaleを掛けたいなら掛ける
                dstRect.w *= mOwner->GetScale();
                dstRect.h *= mOwner->GetScale();

                // 実際に描画 (SDL3関数)
                if (SDL_RenderTexture(renderer,
                    mTextureSplitter.GetSourceTexture(),
                    &srcRect,
                    &dstRect) != 0)
                {
                    SDL_Log("SDL_RenderTexture failed: %s", SDL_GetError());
                }
            }
        }

        // アルファ値を元に戻す
        SDL_SetTextureAlphaMod(mTextureSplitter.GetSourceTexture(), oldAlpha);
    }
}

// 特定の位置(x,y)にあるタイルIDを取得
// layerIndex レイヤー番目から取得。
int TileMapComponent::GetTileAt(int x, int y, int layerIndex) const
{
    if (layerIndex < 0 || layerIndex >= static_cast<int>(mLayers.size()))
    {
        return -1; // 無効
    }
    const auto& layer = mLayers[layerIndex];
    if (y < 0 || y >= static_cast<int>(layer.data.size())) return -1;
    if (x < 0 || x >= static_cast<int>(layer.data[y].size())) return -1;

    return layer.data[y][x];
}

// 特定の位置(x,y)にあるタイルIDを設定
void TileMapComponent::SetTileAt(int x, int y, int tileID, int layerIndex)
{
    if (layerIndex < 0 || layerIndex >= static_cast<int>(mLayers.size()))
    {
        return;
    }
    auto& layer = mLayers[layerIndex];
    if (y < 0 || y >= static_cast<int>(layer.data.size())) return;
    if (x < 0 || x >= static_cast<int>(layer.data[y].size())) return;

    layer.data[y][x] = tileID;
}

// ワールド座標(ピクセル)→タイル座標への変換
// タイル幅・高さで割るだけだが、ビューポートによるオフセットも考慮
Vector2 TileMapComponent::WorldToTile(const Vector2& worldPos) const
{
    float tileX = (worldPos.x + mViewport.x) / mTileWidth;
    float tileY = (worldPos.y + mViewport.y) / mTileHeight;
    return Vector2(tileX, tileY);
}

// タイル座標→ワールド座標(ピクセル)への変換
// 逆にタイル幅・高さを掛ける。ビューポートはあくまで表示上のズレなので
// ここではあまり関係なく、実際にタイルの左上ピクセル座標を返すイメージ。
Vector2 TileMapComponent::TileToWorld(int tileX, int tileY) const
{
    float worldX = tileX * mTileWidth - mViewport.x;
    float worldY = tileY * mTileHeight - mViewport.y;
    return Vector2(worldX, worldY);
}

// 衝突タイルを設定
// tileID→衝突フラグ(bool)をマップに登録
void TileMapComponent::SetCollisionTile(int tileID, bool isCollidable)
{
    mCollisionMap[tileID] = isCollidable;
}

// タイル(x,y,layerIndex)が衝突可能かどうか
bool TileMapComponent::IsTileCollidable(int x, int y, int layerIndex) const
{
    int tileID = GetTileAt(x, y, layerIndex);
    return IsTileIDCollidable(tileID);
}

// タイルIDが衝突可能かどうか
bool TileMapComponent::IsTileIDCollidable(int tileID) const
{
    if (tileID < 0) return false;
    auto it = mCollisionMap.find(tileID);
    if (it != mCollisionMap.end())
    {
        return it->second;
    }
    return false;
}

// レイヤーの可視性を設定
void TileMapComponent::SetLayerVisible(int layerIndex, bool visible)
{
    if (layerIndex < 0 || layerIndex >= static_cast<int>(mLayers.size()))
    {
        return;
    }
    mLayers[layerIndex].visible = visible;
}

// ビューポートを設定
// 表示範囲を(SDL_FRect)で示す。タイル描画時にオフセットとして使う。
void TileMapComponent::SetViewport(const SDL_Rect& viewport)
{
    mViewport.x = static_cast<float>(viewport.x);
    mViewport.y = static_cast<float>(viewport.y);
    mViewport.w = static_cast<float>(viewport.w);
    mViewport.h = static_cast<float>(viewport.h);
}

// マップサイズ(タイル数)を取得
// ここでは第一レイヤーのサイズを返すだけにする。
// より厳密にするなら全レイヤーの最大サイズなど取る。
Vector2 TileMapComponent::GetMapSize() const
{
    if (mLayers.empty()) return Vector2(0.0f, 0.0f);
    const auto& layer = mLayers[0];
    int rows = static_cast<int>(layer.data.size());
    if (rows == 0) return Vector2(0.0f, 0.0f);
    int cols = static_cast<int>(layer.data[0].size());
    return Vector2((float)cols, (float)rows);
}

// マップのピクセルサイズを取得
Vector2 TileMapComponent::GetMapPixelSize() const
{
    Vector2 tileCount = GetMapSize();
    float w = tileCount.x * mTileWidth;
    float h = tileCount.y * mTileHeight;
    return Vector2(w, h);
}

// 可視タイル範囲を計算し、タイル座標空間でのrectを返す
// mViewportに基づいて、「どのタイル範囲を描画すれば良いか」をざっくり求める。
SDL_FRect TileMapComponent::CalculateVisibleTiles() const
{
    // ビューポートが (x, y, w, h)
    // タイル幅,高さで割り算し、端数を丸める形でタイル範囲を求める。
    // x～x+w, y～y+h までの範囲。
    float minTileX = mViewport.x / mTileWidth;
    float minTileY = mViewport.y / mTileHeight;
    float maxTileX = (mViewport.x + mViewport.w) / mTileWidth;
    float maxTileY = (mViewport.y + mViewport.h) / mTileHeight;

    // タイル空間での可視矩形 (x, y, w, h)
    SDL_FRect result;
    result.x = minTileX;
    result.y = minTileY;
    result.w = (maxTileX - minTileX);
    result.h = (maxTileY - minTileY);
    return result;
}
