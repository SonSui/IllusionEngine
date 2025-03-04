#pragma once
#include "IllusionEngine.h"

class TextureSplitter
{
public:
    // �R���X�g���N�^�[
    TextureSplitter(SDL_Renderer* renderer);
    ~TextureSplitter();

    // �e�N�X�`���𕪊����郁�\�b�h
    // offsetX, offsetY: �����J�n�ʒu
    // spacingX, spacingY: �^�C���Ԃ̊Ԋu
    bool SplitTexture(
        SDL_Texture* sourceTexture,
        float tileWidth,
        float tileHeight,
        float offsetX = 0,
        float offsetY = 0,
        float spacingX = 0,
        float spacingY = 0
    );

    // �^�C���̐����擾
    int GetTileCount() const { return static_cast<int>(mTileRects.size()); }

    // ����̃^�C���̕`������擾
    const SDL_FRect& GetTileRect(int index) const;

    // �^�C���̕`����̃��X�g���擾
    const std::vector<SDL_FRect>& GetTileRects() const { return mTileRects; }

	SDL_Texture* GetSourceTexture() const { return mSourceTexture; }
	// �e�N�X�`���̕��ƍ������擾
	int GetTextureWidth() const { return mTextureWidth; }
	int GetTextureHeight() const { return mTextureHeight; }

private:
    // �����_���[
    SDL_Renderer* mRenderer;

    // �\�[�X�e�N�X�`��
    SDL_Texture* mSourceTexture;

    // �^�C���̕`����
    std::vector<SDL_FRect> mTileRects;

    // �e�N�X�`���̕��ƍ���
    float mTextureWidth;
    float mTextureHeight;
};