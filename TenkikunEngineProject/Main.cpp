#include "DxLib.h"
#include <iostream>
#include "GameWindow.h"
#include <vector>
#include "SceneManager.h"
#include <Windows.h>
#include <tchar.h>
#include <mmsystem.h>
#include <string>
#include "Script.h"
#include "PlayerScript.h"
#include "Input.h"
#include "Rotate.h"
#include "WindowManager.h"

#pragma comment(lib,"winmm.lib")

#define WIDTH 600
#define HEIGHT 500

// 本当はグローバルにしない方が良い
const float MIN_FRAME_TIME = 1.0f / 60;
LARGE_INTEGER timeStart;
LARGE_INTEGER timeEnd;
LARGE_INTEGER timeFreq;

void Init();
void CulculateFPS();
void Update();
void Draw();

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	SetMainWindowText("Practice");
	ChangeWindowMode(TRUE); //ウィンドウモードで起動
	SetGraphMode(WIDTH, HEIGHT, 32); //画面の解像度指定
	SetWindowSizeChangeEnableFlag(FALSE); //画面サイズ変更不可
	SetDrawScreen(DX_SCREEN_BACK);	//裏画面で描画

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	// メインループに入る前に精度を取得しておく
	if (QueryPerformanceFrequency(&timeFreq) == FALSE) { // この関数で0(FALSE)が帰る時は未対応
		// そもそもQueryPerformanceFrequencyが使えない様な(古い)PCではどうせ色々キツイだろうし
		return(E_FAIL); // 本当はこんな帰り方しては行けない(後続の解放処理が呼ばれない)
	}
	// 1度取得しておく(初回計算用)
	QueryPerformanceCounter(&timeStart);

	Init();	//初期化

	//メインループ
	while (ProcessMessage() == 0) {
		CulculateFPS();	//FPSの計算

		Update();	//更新

		Draw();	//描画

		ScreenFlip();	//画面裏返す

	}


	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}

inline void Init() {
	SceneManager();	//シーンマネージャーの初期化
	WindowManager();	//ゲーム画面の初期化
	Input();	//入力の初期化

	Scene* scene = SceneManager::GetNowScene();	//シーンを取得

	GameObject* player = scene->CreateEmpty();	//プレイヤーオブジェクトを作成
	player->transform->position = Vector3(0, 0, 0);
	player->name = "Player";
	PlayerScript* script = player->AddComponent<PlayerScript>();	//プレイヤースクリプト作成

	GameObject* square = GameObject::Find("Square");
	square->transform->SetParent(player->transform);
	square->transform->position = Vector3(50, 0, 0);
	square->AddComponent<Rotate>();

	GameObject* square2 = GameObject::Find("Square2");
	square2->transform->SetParent(square->transform);
	square2->transform->position = Vector3(150, 0, 0);
	square2->transform->scale = Vector3(0.5f, 0.5f, 1);
}

inline void CulculateFPS() {
	// 今の時間を取得
	QueryPerformanceCounter(&timeEnd);
	// (今の時間 - 前フレームの時間) / 周波数 = 経過時間(秒単位)
	double frameTime = static_cast<double>(timeEnd.QuadPart - timeStart.QuadPart) / static_cast<double>(timeFreq.QuadPart);

	if (frameTime < MIN_FRAME_TIME) { // 時間に余裕がある
		// ミリ秒に変換
		DWORD sleepTime = static_cast<DWORD>((MIN_FRAME_TIME - frameTime) * 1000);

		timeBeginPeriod(1); // 分解能を上げる(こうしないとSleepの精度はガタガタ)
		Sleep(sleepTime);   // 寝る
		timeEndPeriod(1);   // 戻す
	}

	double fps = 1 / frameTime;

	//OutputDebugString("FPS:");	//FPSを表示
	//OutputDebugString(std::to_string(fps).c_str());	//FPSを表示
	//OutputDebugString("\n");	//FPSを表示

	timeStart = timeEnd; // 入れ替え
}

inline void Update() {
	Scene* scene = SceneManager::GetNowScene();
	scene->Update();	//現在のシーンの更新
	Input::Update();	//キーの更新
}

inline void Draw() {
	//画面全体を黒で描画
	DrawBoxAA(0, 0, WIDTH, HEIGHT, GetColor(0, 0, 0), TRUE);

	WindowManager::Draw();	//ウィンドウ画面を描画
}