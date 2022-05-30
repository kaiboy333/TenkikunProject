#include "WindowManager.h"

void WindowManager::Draw()
{
	gameWindow->Draw();	//ゲーム画面の描画
	hierarchyWindow->Draw();	//ヒエラルキーウィンドウの描画
}

GameWindow* WindowManager::gameWindow = new GameWindow();
HierarchyWindow* WindowManager::hierarchyWindow = new HierarchyWindow();

