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

    // �\�[�X�e�N�X�`���̏����擾
	SDL_GetTextureSize(sourceTexture, &mTextureWidth, &mTextureHeight);

    // �O��̕������ʂ��N���A
    mTileRects.clear();
    mSourceTexture = sourceTexture;

    // �����\�ȗ�ƍs���v�Z
    int columns = (mTextureWidth - offsetX + spacingX) / (tileWidth + spacingX);
    int rows = (mTextureHeight - offsetY + spacingY) / (tileHeight + spacingY);

    // �^�C���̕����Ə��̕ۑ�
    for (int y = 0; y < rows; ++y)
    {
        for (int x = 0; x < columns; ++x)
        {
            // �^�C���̈ʒu�Ƒ傫�����v�Z
            SDL_FRect tileRect;
            tileRect.x = offsetX + x * (tileWidth + spacingX);
            tileRect.y = offsetY + y * (tileHeight + spacingY);
            tileRect.w = static_cast<float>(tileWidth);
            tileRect.h = static_cast<float>(tileHeight);

            // �^�C������ۑ�
            mTileRects.push_back(tileRect);
        }
    }

    return true;
}

const SDL_FRect& TextureSplitter::GetTileRect(int index) const
{
    // SDL_FRect ���R�s�[���Ȃ�����"&"�𗘗p
    if (index < 0 || index >= static_cast<int>(mTileRects.size()))
    {
        // �G���[�n���h�����O�F�ÓI�ȋ��SDL_FRect��Ԃ�
        static SDL_FRect emptyRect = { 0, 0, 0, 0 };
        return emptyRect;
    }
    return mTileRects[index];
}