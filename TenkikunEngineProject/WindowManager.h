#pragma once

#include "Window.h"
#include "GameWindow.h"
#include "HierarchyWindow.h"
#include "InspectorWindow.h"

class GameWindow;
class HierarchyWindow;
class InspectorWindow;
class WindowManager
{
	public:
		static GameWindow* gameWindow;
		static HierarchyWindow* hierarchyWindow;
		static InspectorWindow* inspectorWindow;

		static Window* activeWindow;

		static void Update();	//画面のマウスチェック
		static void Draw();

		static vector<Window*> GetWindows();	//現在あるすべてのウィンドウを取得

		static bool canUseGameWnd;	//ゲーム画面が反応するか
};

