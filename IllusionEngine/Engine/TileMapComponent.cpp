#include "TileMapComponent.h"
#include "Actor.h"
#include <fstream>
#include <sstream>
#include <algorithm>

TileMapComponent::TileMapComponent(Actor* owner, int drawOrder)
    : SpriteComponent(owner, drawOrder)
    , mTileSheet(nullptr)
    , mTileWidth(32)
    , mTileHeight(32)
    , mTilesPerRow(1)
    , mMapWidth(0)
    , mMapHeight(0)
{
    // デフォルトのビューポートを全画面に設定
    mViewport = { 0, 0, 1280, 720 }; // 仮の解像度
    mOwner->GetGame()->AddSprite(this);
}

TileMapComponent::~TileMapComponent()
{
    // デストラクタ：mTileSheetは外部から渡されるため解放不要
}

void TileMapComponent::Draw(SDL_Renderer* renderer)
{
    if (!mTileSheet || mLayers.empty())
    {
        return;
    }

    // 可視領域内のタイル範囲を計算
    SDL_FRect visibleTiles = CalculateVisibleTiles();

    // Z順にレイヤーをソート
    std::vector<int> layerIndices(mLayers.size());
    for (int i = 0; i < static_cast<int>(mLayers.size()); i++)
    {
        layerIndices[i] = i;
    }

    std::sort(layerIndices.begin(), layerIndices.end(), [this](int a, int b) {
        return mLayers[a].zOrder < mLayers[b].zOrder;
        });

    // 各レイヤーを描画
    for (int layerIdx : layerIndices)
    {
        const Layer& layer = mLayers[layerIdx];
        if (!layer.visible)
        {
            continue;
        }

        // アクターの位置（マップの原点）を取得
        Vector2 actorPos = mOwner->GetPosition();

        // 可視領域内のタイルを走査
        for (int y = static_cast<int>(visibleTiles.y); y < static_cast<int>(visibleTiles.y + visibleTiles.h) && y < mMapHeight; y++)
        {
            for (int x = static_cast<int>(visibleTiles.x); x < static_cast<int>(visibleTiles.x + visibleTiles.w) && x < mMapWidth; x++)
            {
                // タイルIDを取得
                int tileID = layer.data[y][x];
                if (tileID < 0) continue; // 空タイルはスキップ

                // タイルのワールド座標を計算し、ビューポート分補正してスクリーン座標に変換
                SDL_FRect destRect;
                destRect.x = static_cast<int>(actorPos.x) + x * mTileWidth - mViewport.x;
                destRect.y = static_cast<int>(actorPos.y) + y * mTileHeight - mViewport.y;
                destRect.w = mTileWidth;
                destRect.h = mTileHeight;

                // タイルシート上のタイル矩形を取得
                SDL_FRect srcRect = GetSourceRect(tileID);

                // タイルを描画（SDL3のSDL_RenderTextureを使用）
                SDL_RenderTexture(renderer, mTileSheet, &srcRect, &destRect);
            }
        }
    }
}

void TileMapComponent::Update(float deltaTime)
{
    // ここにアニメーションタイルの更新や自動タイルルールの更新ロジックを追加可能
}

bool TileMapComponent::LoadTileMap(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        return false;
    }

    std::vector<std::vector<int>> tileData;
    std::string line;
    while (std::getline(file, line))
    {
        std::vector<int> row;
        std::stringstream ss(line);
        std::string cell;

        while (std::getline(ss, cell, ','))
        {
            row.push_back(std::stoi(cell));
        }

        tileData.push_back(row);
    }

    return LoadTileMap(tileData);
}

bool TileMapComponent::LoadTileMap(const std::vector<std::vector<int>>& tileData)
{
    if (tileData.empty() || tileData[0].empty())
    {
        return false;
    }

    mTileData = tileData;
    mMapHeight = static_cast<int>(tileData.size());
    mMapWidth = static_cast<int>(tileData[0].size());

    // ベースレイヤーを作成し、データを追加
    Layer baseLayer;
    baseLayer.data = tileData;
    baseLayer.visible = true;
    baseLayer.zOrder = 0;

    mLayers.clear();
    mLayers.push_back(baseLayer);

    return true;
}

void TileMapComponent::SetTileSheet(SDL_Texture* tilesheet, int tileWidth, int tileHeight, int tilesPerRow)
{
    mTileSheet = tilesheet;
    mTileWidth = tileWidth;
    mTileHeight = tileHeight;
    mTilesPerRow = tilesPerRow;
}

int TileMapComponent::GetTileAt(int x, int y) const
{
    if (x < 0 || x >= mMapWidth || y < 0 || y >= mMapHeight || mLayers.empty())
    {
        return -1; // 無効な値
    }

    return mLayers[0].data[y][x]; // ベースレイヤーのタイルを返す
}

void TileMapComponent::SetTileAt(int x, int y, int tileID)
{
    if (x < 0 || x >= mMapWidth || y < 0 || y >= mMapHeight || mLayers.empty())
    {
        return;
    }

    mLayers[0].data[y][x] = tileID;
}

Vector2 TileMapComponent::WorldToTile(const Vector2& worldPos) const
{
    Vector2 actorPos = mOwner->GetPosition();
    float tileX = (worldPos.x - actorPos.x) / mTileWidth;
    float tileY = (worldPos.y - actorPos.y) / mTileHeight;

    return Vector2(tileX, tileY);
}

Vector2 TileMapComponent::TileToWorld(int tileX, int tileY) const
{
    Vector2 actorPos = mOwner->GetPosition();
    float worldX = actorPos.x + tileX * mTileWidth;
    float worldY = actorPos.y + tileY * mTileHeight;

    return Vector2(worldX, worldY);
}

void TileMapComponent::AddAutoTileRule(int sourceTileID, const std::vector<int>& neighborPattern, int resultTileID)
{
    AutoTileRule rule;
    rule.sourceTileID = sourceTileID;
    rule.neighborPattern = neighborPattern;
    rule.resultTileID = resultTileID;

    mAutoTileRules.push_back(rule);
}

void TileMapComponent::ApplyAutoTileRules()
{
    if (mLayers.empty() || mAutoTileRules.empty())
    {
        return;
    }

    // 一時的なタイルデータを作成して、ルール適用後の結果を保存
    std::vector<std::vector<int>> newTileData = mLayers[0].data;

    for (int y = 0; y < mMapHeight; y++)
    {
        for (int x = 0; x < mMapWidth; x++)
        {
            int currentTile = mLayers[0].data[y][x];

            // 各ルールをチェック
            for (const AutoTileRule& rule : mAutoTileRules)
            {
                if (currentTile == rule.sourceTileID)
                {
                    // 8方向の隣接タイルを取得
                    std::vector<int> neighbors(8, -1);

                    // 順番：左上、上、右上、右、右下、下、左下、左
                    if (x > 0 && y > 0) neighbors[0] = mLayers[0].data[y - 1][x - 1];
                    if (y > 0) neighbors[1] = mLayers[0].data[y - 1][x];
                    if (y > 0 && x < mMapWidth - 1) neighbors[2] = mLayers[0].data[y - 1][x + 1];
                    if (x < mMapWidth - 1) neighbors[3] = mLayers[0].data[y][x + 1];
                    if (y < mMapHeight - 1 && x < mMapWidth - 1) neighbors[4] = mLayers[0].data[y + 1][x + 1];
                    if (y < mMapHeight - 1) neighbors[5] = mLayers[0].data[y + 1][x];
                    if (y < mMapHeight - 1 && x > 0) neighbors[6] = mLayers[0].data[y + 1][x - 1];
                    if (x > 0) neighbors[7] = mLayers[0].data[y][x - 1];

                    // 隣接パターンが一致するか確認
                    bool match = true;
                    for (size_t i = 0; i < rule.neighborPattern.size() && i < neighbors.size(); i++)
                    {
                        if (rule.neighborPattern[i] != -1 && rule.neighborPattern[i] != neighbors[i])
                        {
                            match = false;
                            break;
                        }
                    }

                    if (match)
                    {
                        newTileData[y][x] = rule.resultTileID;
                        break; // 最初に一致したルールを適用
                    }
                }
            }
        }
    }

    // 新しいタイルデータを適用
    mLayers[0].data = newTileData;
}

void TileMapComponent::SetCollisionTile(int tileID, bool isCollidable)
{
    mCollisionMap[tileID] = isCollidable;
}

bool TileMapComponent::IsTileCollidable(int x, int y) const
{
    int tileID = GetTileAt(x, y);
    return IsTileIDCollidable(tileID);
}

bool TileMapComponent::IsTileIDCollidable(int tileID) const
{
    auto it = mCollisionMap.find(tileID);
    if (it != mCollisionMap.end())
    {
        return it->second;
    }
    return false; // デフォルトは衝突しない
}

void TileMapComponent::AddLayer(const std::vector<std::vector<int>>& layerData, int zOrder)
{
    if (layerData.empty() || layerData[0].empty() ||
        layerData.size() != static_cast<size_t>(mMapHeight) ||
        layerData[0].size() != static_cast<size_t>(mMapWidth))
    {
        return; // レイヤーのサイズは一致している必要がある
    }

    Layer newLayer;
    newLayer.data = layerData;
    newLayer.visible = true;
    newLayer.zOrder = zOrder;

    mLayers.push_back(newLayer);
}

void TileMapComponent::SetLayerVisible(int layerIndex, bool visible)
{
    if (layerIndex >= 0 && layerIndex < static_cast<int>(mLayers.size()))
    {
        mLayers[layerIndex].visible = visible;
    }
}

SDL_FRect TileMapComponent::GetSourceRect(int tileID) const
{
    SDL_FRect src;

    // タイルシート上の行と列を計算
    int row = tileID / mTilesPerRow;
    int col = tileID % mTilesPerRow;

    src.x = col * mTileWidth;
    src.y = row * mTileHeight;
    src.w = mTileWidth;
    src.h = mTileHeight;

    return src;
}

SDL_FRect TileMapComponent::CalculateVisibleTiles() const
{
    SDL_FRect visibleTiles;

    Vector2 actorPos = mOwner->GetPosition();

    // 可視領域内の最初のタイルを計算
    visibleTiles.x = static_cast<int>((mViewport.x - actorPos.x) / mTileWidth);
    visibleTiles.y = static_cast<int>((mViewport.y - actorPos.y) / mTileHeight);

    // 負のインデックスを防止
    visibleTiles.x = std::max(0.0f, visibleTiles.x);
    visibleTiles.y = std::max(0.0f, visibleTiles.y);

    // 可視領域内のタイル数を計算（境界タイルを確実に表示するため+2）
    visibleTiles.w = static_cast<int>(mViewport.w / mTileWidth) + 2;
    visibleTiles.h = static_cast<int>(mViewport.h / mTileHeight) + 2;

    // マップ境界を超えないように調整
    visibleTiles.w = std::min(visibleTiles.w, mMapWidth - static_cast<float>(visibleTiles.x));
    visibleTiles.h = std::min(visibleTiles.h, mMapHeight - static_cast<float>(visibleTiles.y));

    return visibleTiles;
}
