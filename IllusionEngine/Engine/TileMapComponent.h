#pragma once
#include "SpriteComponent.h"
#include <vector>
#include <string>
#include <unordered_map>

// タイルマップコンポーネントクラス
class TileMapComponent : public SpriteComponent
{
public:
    // コンストラクタ
    TileMapComponent(class Actor* owner, int drawOrder = 90);
    // デストラクタ
    ~TileMapComponent();

    // 描画メソッドのオーバーライド
    virtual void Draw(SDL_Renderer* renderer) override;
    // 更新メソッドのオーバーライド
    virtual void Update(float deltaTime) override;
    // コンポーネントタイプを取得
    virtual uint64_t GetComponentType() override { return static_cast<uint64_t>(ComponentType::TileMap); }

    // ファイルからタイルマップを読み込む（CSV形式またはカスタム形式に対応）
    bool LoadTileMap(const std::string& filename);
    // 二次元配列からタイルマップを読み込む
    bool LoadTileMap(const std::vector<std::vector<int>>& tileData);

    // タイルシート（全タイルを含む大きな画像）を設定
    void SetTileSheet(SDL_Texture* tilesheet, int tileWidth, int tileHeight, int tilesPerRow);

    // タイルサイズを設定
    void SetTileSize(int width, int height) { mTileWidth = width; mTileHeight = height; }

    // タイルサイズを取得
    Vector2 GetTileSize() const { return Vector2(static_cast<float>(mTileWidth), static_cast<float>(mTileHeight)); }

    // マップサイズ（タイル数）を取得
    Vector2 GetMapSize() const { return Vector2(static_cast<float>(mMapWidth), static_cast<float>(mMapHeight)); }

    // マップのピクセルサイズを取得
    Vector2 GetMapPixelSize() const { return Vector2(static_cast<float>(mMapWidth * mTileWidth), static_cast<float>(mMapHeight * mTileHeight)); }

    // 座標からタイルIDを取得
    int GetTileAt(int x, int y) const;

    // 特定位置のタイルを設定
    void SetTileAt(int x, int y, int tileID);

    // ワールド座標からタイル座標に変換
    Vector2 WorldToTile(const Vector2& worldPos) const;

    // タイル座標からワールド座標に変換（タイルの左上隅の位置を返す）
    Vector2 TileToWorld(int tileX, int tileY) const;

    // 自動タイルルールを追加（例：自動連結タイル）
    void AddAutoTileRule(int sourceTileID, const std::vector<int>& neighborPattern, int resultTileID);

    // 自動タイルルールを適用
    void ApplyAutoTileRules();

    // 描画領域を設定（最適化のため、可視領域のみ描画）
    void SetViewport(const SDL_Rect& viewport) { mViewport = viewport; }

    // 衝突検知用タイルを設定
    void SetCollisionTile(int tileID, bool isCollidable);
    bool IsTileCollidable(int x, int y) const;
    bool IsTileIDCollidable(int tileID) const;

    // レイヤーを追加（複数レイヤーの合成が可能）
    void AddLayer(const std::vector<std::vector<int>>& layerData, int zOrder = 0);
    void SetLayerVisible(int layerIndex, bool visible);

private:
    // タイルデータ
    std::vector<std::vector<int>> mTileData;
    // 複数レイヤー対応
    struct Layer {
        std::vector<std::vector<int>> data;
        bool visible;
        int zOrder;
    };
    std::vector<Layer> mLayers;

    // タイルシートテクスチャ
    SDL_Texture* mTileSheet;

    // 各タイルのサイズ
    int mTileWidth;
    int mTileHeight;

    // タイルシート内の1行あたりのタイル数
    int mTilesPerRow;

    // マップサイズ（タイル数）
    int mMapWidth;
    int mMapHeight;

    // ビューポート（描画領域）
    SDL_Rect mViewport;

    // 衝突情報
    std::unordered_map<int, bool> mCollisionMap;

    // 自動タイルルール
    struct AutoTileRule {
        int sourceTileID;
        std::vector<int> neighborPattern; // 周囲8方向のタイルパターン
        int resultTileID;
    };
    std::vector<AutoTileRule> mAutoTileRules;

    // タイルIDからタイルシート上の矩形を取得
    SDL_FRect GetSourceRect(int tileID) const;

    // 補助メソッド：画面上に可視なタイル範囲を計算
    SDL_FRect CalculateVisibleTiles() const;
};
