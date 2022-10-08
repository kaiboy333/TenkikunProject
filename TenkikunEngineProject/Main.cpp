#include "DxLib.h"
#include <iostream>
#include "GameWindow.h"
#include <vector>
#include "SceneManager.h"
#include <tchar.h>
#include <mmsystem.h>
#include <string>
#include "PlayerScript.h"
#include "Input.h"
#include "Rotate.h"
#include "ImageManager.h"
#include "resource.h"
#include "ProjectFileManager.h"
#include "FontManager.h"
#include "Debug.h"
#include "Time.h"

#pragma comment(lib,"winmm.lib")

// 本当はグローバルにしない方が良い

void Init();
void Update();
void Draw();

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	SetMainWindowText("Tenkikun Engine");
	ChangeWindowMode(TRUE); //ウィンドウモードで起動
	SetGraphMode((int)WindowManager::WIDTH, (int)WindowManager::HEIGHT, 32); //画面の解像度指定
	SetWindowSizeChangeEnableFlag(FALSE); //画面サイズ変更不可
	SetDrawScreen(DX_SCREEN_BACK);	//裏画面で描画
	SetWindowIconID(IDI_TENKIKUN);	//ウィンドウアイコン設定
	DragFileInfoClear();	//ドロップファイル情報の初期化
	SetAlwaysRunFlag(true);		//バックグラウンドでも動作を継続
	SetDragFileValidFlag(true);		//ドラッグアンドドロップを許可


	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}


	Init();	//初期化

	//メインループ
	while (ProcessMessage() == 0) {
		Update();	//更新

		Draw();	//描画

		ScreenFlip();	//画面裏返す
	}


	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}

inline void Init() {
	Time();	//タイムマネージャーの初期化
	ProjectFileManager();	//ファイルマネージャーの初期化
	ImageManager();	//イメージマネージャーの初期化
	FontManager();	//フォントマネージャーの初期化
	WindowManager();	//ゲーム画面の初期化
	SceneManager();	//シーンマネージャーの初期化
	Input();	//入力の初期化
}

inline void Update() {
	Time::Update();	//時間の更新
	ProjectFileManager::Update(); //ProjectFileManagerの更新
	WindowManager::Update();	//Windowの更新
	Input::Update();	//キーの更新
}

inline void Draw() {
	WindowManager::Draw();	//ウィンドウ画面を描画
}