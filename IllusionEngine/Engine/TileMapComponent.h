#pragma once
#include "SpriteComponent.h"
#include "TextureSplitter.h"
#include <vector>
#include <string>
#include <unordered_map>

class TileMapComponent : public SpriteComponent
{
public:
    // レイヤー構造体
    struct Layer {
        std::vector<std::vector<int>> data;
        bool visible;
        float opacity;
        int zOrder;
    };

    // コンストラクター
    TileMapComponent(
        class Actor* owner,
        SDL_Renderer* renderer,
        int updateOrder = 90
    );

    // タイルシートを設定
    void SetTileSheet(
        SDL_Texture* tilesheet,
        float tileWidth,
        float tileHeight,
        float offsetX = 0,
        float offsetY = 0,
        float spacingX = 0,
        float spacingY = 0
    );

    // CSVファイルからマップをロード
    bool LoadMapFromCSV(const std::string& filename);

    // 2次元配列からマップをロード
    bool LoadMap(const std::vector<std::vector<int>>& mapData);

    // レイヤーを追加
    void AddLayer(
        const std::vector<std::vector<int>>& layerData,
        int zOrder = 0,
        bool visible = true,
        float opacity = 1.0f
    );

    // 描画
    void Draw(SDL_Renderer* renderer);

    // 特定の位置のタイルIDを取得
    int GetTileAt(int x, int y, int layerIndex = 0) const;

    // 特定の位置のタイルIDを設定
    void SetTileAt(int x, int y, int tileID, int layerIndex = 0);

    // ワールド座標からタイル座標に変換
    Vector2 WorldToTile(const Vector2& worldPos) const;

    // タイル座標からワールド座標に変換
    Vector2 TileToWorld(int tileX, int tileY) const;

    // 衝突タイルを設定
    void SetCollisionTile(int tileID, bool isCollidable);

    // タイルが衝突可能かチェック
    bool IsTileCollidable(int x, int y, int layerIndex = 0) const;
    bool IsTileIDCollidable(int tileID) const;

    // レイヤーの可視性を設定
    void SetLayerVisible(int layerIndex, bool visible);

    // ビューポートを設定（表示範囲）
    void SetViewport(const SDL_Rect& viewport);

    // マップサイズを取得
    Vector2 GetMapSize() const;
    Vector2 GetMapPixelSize() const;

    // コンポーネントの種類を取得
    virtual uint64_t GetComponentType() override
    {
        return static_cast<uint64_t>(ComponentType::TileMap);
    }

private:
    // テクスチャ分割クラス
    TextureSplitter mTextureSplitter;

    // レンダラー
    SDL_Renderer* mRenderer;

    // タイルの幅と高さ
    float mTileWidth;
    float mTileHeight;

    // マップのレイヤー
    std::vector<Layer> mLayers;

    // 衝突マップ
    std::unordered_map<int, bool> mCollisionMap;

    // ビューポート（表示範囲）
    SDL_FRect mViewport;

    // 可視タイル範囲を計算
    SDL_FRect CalculateVisibleTiles() const;
};