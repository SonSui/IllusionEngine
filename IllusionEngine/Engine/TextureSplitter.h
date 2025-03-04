#pragma once
#include "IllusionEngine.h"

class TextureSplitter
{
public:
    // コンストラクター
    TextureSplitter(SDL_Renderer* renderer);
    ~TextureSplitter();

    // テクスチャを分割するメソッド
    // offsetX, offsetY: 分割開始位置
    // spacingX, spacingY: タイル間の間隔
    bool SplitTexture(
        SDL_Texture* sourceTexture,
        float tileWidth,
        float tileHeight,
        float offsetX = 0,
        float offsetY = 0,
        float spacingX = 0,
        float spacingY = 0
    );

    // タイルの数を取得
    int GetTileCount() const { return static_cast<int>(mTileRects.size()); }

    // 特定のタイルの描画情報を取得
    const SDL_FRect& GetTileRect(int index) const;

    // タイルの描画情報のリストを取得
    const std::vector<SDL_FRect>& GetTileRects() const { return mTileRects; }

	SDL_Texture* GetSourceTexture() const { return mSourceTexture; }
	// テクスチャの幅と高さを取得
	int GetTextureWidth() const { return mTextureWidth; }
	int GetTextureHeight() const { return mTextureHeight; }

private:
    // レンダラー
    SDL_Renderer* mRenderer;

    // ソーステクスチャ
    SDL_Texture* mSourceTexture;

    // タイルの描画情報
    std::vector<SDL_FRect> mTileRects;

    // テクスチャの幅と高さ
    float mTextureWidth;
    float mTextureHeight;
};