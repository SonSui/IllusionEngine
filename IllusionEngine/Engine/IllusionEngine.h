#pragma once
#include "SDL3/SDL.h"
#include "SDL3_image/SDL_image.h"
#include "SDL3/SDL_joystick.h"
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
	void RemoveActor(Actor* actor);
	void AddSprite(SpriteComponent* sprite);
	void RemoveSprite(SpriteComponent* sprite);
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
	// 描画
	void EngineRender();
	// 実行中確認
	bool mIsRunning;
protected:
	
	// 起動前の設定
	virtual void EnginePreSetting();
	// Game初期化/終了処理
	virtual void Initialize();
	virtual void Finalize();
	// フレイム処理の中身
	virtual void ProcessInput();
	virtual void Update();
	virtual void GenerateOutput();

	

	
	// 起動設定
	Vector2 mWindowSize;
	std::string mWindowName;
	// ゲームのウィンド
	SDL_Window* mWindow;
	// 描画
	SDL_Renderer* mRenderer;
	// 画像
	SDL_Texture* mTexture;
	// 画像配列
	std::unordered_map<std::string, SDL_Texture*> mTextures;

	// 開始からの時間
	Uint32 mTicksCount;
	// 前のフレームからの時間
	float deltaTime;

	// キーボード入力配列
	const bool* SDL_Input;


	// Actor管理
	bool mUpdatingActors;
	std::vector<Actor*> mActors;
	std::vector<Actor*> mPendingActors;
	// 描画順
	std::vector<SpriteComponent* > mSprites;
	

};
