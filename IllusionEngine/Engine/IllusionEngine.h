#pragma once
#include "SDL3/SDL.h"
#include "SDL3_image/SDL_image.h"
#include "IMath.h"
#include "Component.h"
#include "Actor.h"
#include <vector>
#include <algorithm>
#include <unordered_map>







class SpriteComponent;

class GameMain {

public:
	GameMain();
	// 初期化
	bool EngineInitialize();
	// フレイム処理
	void RunLoop();
	// 全体終了処理
	void Shutdown();


	
	void AddActor(Actor* actor);
	void AddSprite(SpriteComponent* sprite);
	SDL_Texture* GetTexture(const std::string& fileName);

	Vector2 GetWidowSize() { return mWindowSize; }
	void SetWindowSize(Vector2 size) { mWindowSize = size; }
	std::string GetWindowName() { return mWindowName; }
	void SetWindowName(std::string name) { mWindowName = name; };
private:
	// レンダ初期化
	bool InitializeRenderer(SDL_Window* _mWindow, SDL_Renderer** _mRenderer);
	// フレーム更新
	void UpdateGame();
	// 入力
	void EngineInput();
	// 実行中確認
	bool mIsRunning;
protected:
	
	virtual void EnginePreSetting();
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
	std::unordered_map<std::string, SDL_Texture*> mTextures;

	// 開始からの時間
	Uint32 mTicksCount;


	float deltaTime;

	const bool* SDL_Input;


	
	bool mUpdatingActors;
	std::vector<Actor*> mActors;
	std::vector<Actor*> mPendingActors;
	// 描画順
	std::vector<SpriteComponent* > mSprites;
	
	Vector2 mWindowSize;
	std::string mWindowName;
	
};
