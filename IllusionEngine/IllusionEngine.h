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

		if (dec > 10) dec = 10;// 最大10桁まで制限

		// フォーマット文字列を作成
		std::snprintf(format, sizeof(format), "(%%.%df, %%.%df)", dec, dec);

		std::snprintf(buffer, sizeof(buffer), format, x, y);
		return buffer;
	}
};

class GameMain {

public:
	GameMain();
	// 初期化
	bool EngineInitialize();
	// フレイム処理
	void RunLoop();
	// 全体終了処理
	void Shutdown();
private:
	// レンダ初期化
	bool InitializeRenderer(SDL_Window* _mWindow, SDL_Renderer** _mRenderer);
	void UpdateGame();
protected:
	// Game初期化/終了処理
	virtual void Initialize();
	virtual void Finalize();
	// フレイム処理の中身
	virtual void ProcessInput();
	virtual void Update();
	virtual void GenerateOutput();
	

	// ゲームのウィンド
	SDL_Window* mWindow;
	// 描画
	SDL_Renderer* mRenderer;
	// 画像
	SDL_Texture* mTexture;
	// 開始からの時間
	Uint32 mTicksCount;
	// ゲーム実行中の判断
	bool mIsRunning;

	float deltaTime;

};
