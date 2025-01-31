#pragma once
#include "SDL3/SDL.h"
#include "SDL3_image/SDL_image.h"
#include <cmath>
#include <random>
#include <iostream>
#include <cstdio>

#define TICKS_PASSED(a, b) ((Sint64)((a) - (b)) >= 0)

struct Vector2
{
	float x;
	float y;
	Vector2(float _x = 0.0f, float _y = 0.0f) : x(_x), y(_y) {}

	Vector2 operator+(const Vector2& other) const
	{
		return Vector2(x + other.x, y + other.y);
	}

	Vector2 operator-(const Vector2& other) const
	{
		return Vector2(x - other.x, y - other.y);
	}

	bool operator==(const Vector2& other) const
	{
		return (x == other.x) && (y == other.y);
	}

	float length() const
	{
		return std::sqrt(x * x + y * y);
	}


	Vector2 normalized() const {
		float len = length();
		if (len == 0) return Vector2(0, 0);
		return Vector2(x / len, y / len);
	}

	const char* toString(unsigned int dec = 2)
	{
		static char buffer[50];
		static char format[20];

		if (dec > 10) dec = 10;// �ő�10���܂Ő���

		// �t�H�[�}�b�g��������쐬
		std::snprintf(format, sizeof(format), "(%%.%df, %%.%df)", dec, dec);

		std::snprintf(buffer, sizeof(buffer), format, x, y);
		return buffer;
	}
};

class GameMain {

public:
	GameMain();
	// ������
	bool EngineInitialize();
	// �t���C������
	void RunLoop();
	// �S�̏I������
	void Shutdown();
private:
	// �����_������
	bool InitializeRenderer(SDL_Window* _mWindow, SDL_Renderer** _mRenderer);
	void UpdateGame();
protected:
	// Game������/�I������
	virtual void Initialize();
	virtual void Finalize();
	// �t���C�������̒��g
	virtual void ProcessInput();
	virtual void Update();
	virtual void GenerateOutput();
	

	// �Q�[���̃E�B���h
	SDL_Window* mWindow;
	// �`��
	SDL_Renderer* mRenderer;
	// �摜
	SDL_Texture* mTexture;
	// �J�n����̎���
	Uint32 mTicksCount;
	// �Q�[�����s���̔��f
	bool mIsRunning;

	float deltaTime;

};
