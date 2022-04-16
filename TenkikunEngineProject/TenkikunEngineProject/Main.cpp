#include "DxLib.h"

#define WIDTH 600
#define HEIGHT 500

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
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

	//メインループ
	while (ProcessMessage() == 0) {
		//画面全体を黒で描画
		DrawBoxAA(0, 0, WIDTH, HEIGHT, GetColor(0, 0, 0), TRUE);

		//四角形を描画
		DrawBoxAA(WIDTH / 2.0 - WIDTH / 4.0, HEIGHT / 2.0 - HEIGHT / 4.0, WIDTH / 2.0 + WIDTH / 4.0, HEIGHT / 2.0 + HEIGHT / 4.0, GetColor(255, 255, 255), TRUE);


		DrawPixel(320, 240, GetColor(255, 255, 255));	// 点を打つ

		ScreenFlip();	//画面裏返す

	}


	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}