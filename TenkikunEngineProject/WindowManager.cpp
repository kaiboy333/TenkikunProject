#include "WindowManager.h"

GameWindow WindowManager::gameWindow = GameWindow(700, 500);

void WindowManager::Draw()
{
	gameWindow.Draw();	//ゲーム画面の描画
}
