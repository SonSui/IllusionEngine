#include "TextureSplitter.h"
#include "IllusionEngine.h"

TextureSplitter::TextureSplitter(SDL_Renderer* renderer)
    : mRenderer(renderer)
    , mSourceTexture(nullptr)
    , mTextureWidth(0)
    , mTextureHeight(0)
{
}

TextureSplitter::~TextureSplitter()
{
    mTileRects.clear();
}

bool TextureSplitter::SplitTexture(
    SDL_Texture* sourceTexture,
    float tileWidth,
    float tileHeight,
    float offsetX,
    float offsetY,
    float spacingX,
    float spacingY
)
{
    if (!sourceTexture)
    {
        return false;
    }

    // ソーステクスチャの情報を取得
	SDL_GetTextureSize(sourceTexture, &mTextureWidth, &mTextureHeight);

    // 前回の分割結果をクリア
    mTileRects.clear();
    mSourceTexture = sourceTexture;

    // 分割可能な列と行を計算
    int columns = (mTextureWidth - offsetX + spacingX) / (tileWidth + spacingX);
    int rows = (mTextureHeight - offsetY + spacingY) / (tileHeight + spacingY);

    // タイルの分割と情報の保存
    for (int y = 0; y < rows; ++y)
    {
        for (int x = 0; x < columns; ++x)
        {
            // タイルの位置と大きさを計算
            SDL_FRect tileRect;
            tileRect.x = offsetX + x * (tileWidth + spacingX);
            tileRect.y = offsetY + y * (tileHeight + spacingY);
            tileRect.w = static_cast<float>(tileWidth);
            tileRect.h = static_cast<float>(tileHeight);

            // タイル情報を保存
            mTileRects.push_back(tileRect);
        }
    }

    return true;
}

const SDL_FRect& TextureSplitter::GetTileRect(int index) const
{
    // SDL_FRect をコピーしないため"&"を利用
    if (index < 0 || index >= static_cast<int>(mTileRects.size()))
    {
        // エラーハンドリング：静的な空のSDL_FRectを返す
        static SDL_FRect emptyRect = { 0, 0, 0, 0 };
        return emptyRect;
    }
    return mTileRects[index];
}