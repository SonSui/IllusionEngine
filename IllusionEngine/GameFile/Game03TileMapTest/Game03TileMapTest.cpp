#include "Game03TileMapTest.h"

#define TILEMAP_TEXTURE "GameFile/Game03TileMapTest/Assets/Tileset.png"

// エンジン事前設定
void Game03TileMapTest::EnginePreSetting()
{
    SetWindowSize(Vector2(_WINDOW_WIDTH, _WINDOW_HEIGHT));
    SetWindowName(_WINDOW_NAME);
}

// 初期化処理
void Game03TileMapTest::Initialize()
{
    Actor* temp = new Actor(this);
    // タイルマップコンポーネントを作成
    //mTileMap = new TileMapComponent(temp, 100);

    // タイルシートテクスチャを読み込む
    SDL_Texture* tileSheet = GetTexture(TILEMAP_TEXTURE);
    mTileMap->SetTileSheet(tileSheet, 32, 32, 8); // 32x32のタイル、1行あたり8個

    //// 方法1：ファイルからタイルマップを読み込む
    //mTileMap->LoadTileMap("Assets/Maps/level1.csv");

    // 方法2：手動でタイルマップを作成
    std::vector<std::vector<int>> mapData = {
        {-1, 1, 1, 1, 1, 1, 1, 0},
        {2, 4, 3, 3, 3, 3, 3, 4},
        {2, 3, 3, 3, 3, 3, 3, 4},
        {2, 3, 3, 3, 2, 3, 3, 4},
        {5, 8, 8, 8, 8, 8, 8, 9}
    };
    //mTileMap->LoadTileMap(mapData);

    // 第2レイヤー（装飾レイヤー）を追加
    std::vector<std::vector<int>> decorLayer(5, std::vector<int>(8, -1)); // 全体を初期化（-1で空）
    decorLayer[1][3] = 10; // (3,1)に装飾タイルを配置
    decorLayer[2][5] = 11; // (5,2)に装飾タイルを配置
    mTileMap->AddLayer(decorLayer, 1); // zOrder=1：上レイヤーとして表示

    //// 衝突タイルの設定
    //mTileMap->SetCollisionTile(0, true);  // 壁タイル
    //mTileMap->SetCollisionTile(1, true);  // 壁タイル
    //mTileMap->SetCollisionTile(2, true);  // 壁タイル
    //// ... その他の衝突タイル設定

    //// 自動タイルルールの設定（例：自動連結壁タイル）
    //// 例：タイル3の上にタイル1がある場合、タイル3をタイル8に変更
    //std::vector<int> pattern = { -1, 1, -1, -1, -1, -1, -1, -1 };
    //mTileMap->AddAutoTileRule(3, pattern, 8);
    //mTileMap->ApplyAutoTileRules();
}

void Game03TileMapTest::Finalize()
{
    // 終了処理
}

void Game03TileMapTest::ProcessInput()
{
    // 入力処理
}

void Game03TileMapTest::Update()
{
    // 更新処理
}

void Game03TileMapTest::GenerateOutput()
{
    // 出力生成処理
}
