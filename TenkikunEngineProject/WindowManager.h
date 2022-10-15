#pragma once

#include "Window.h"
#include "GameWindow.h"
#include "HierarchyWindow.h"
#include "InspectorWindow.h"
#include "ProjectWindow.h"
#include "MenuList.h"
#include "PlayWindow.h"

class GameWindow;
class HierarchyWindow;
class InspectorWindow;
class ProjectWindow;
class WindowManager : Rect
{
	public:
		static GameWindow* gameWindow;
		static HierarchyWindow* hierarchyWindow;
		static InspectorWindow* inspectorWindow;
		static ProjectWindow* projectWindow;
		static PlayWindow* playWindow;

		//static Window* activeWindow;

		static const float WIDTH;
		static const float HEIGHT;

		WindowManager();

		static void Update();	//画面のマウスチェック
		static void Draw();

		static vector<Window*> GetWindows();	//現在あるすべてのウィンドウを取得

		static void SetSelectedTriggerRect(TriggerRect* selectedTriggerRect);	//指定のTriggerRectを選択された状態にする(前のは解除)
		static void ClearSelectedTriggerRect();	//すべての選択された状態のTriggerRectを解除する

		static TriggerRect* GetSelectedTriggerRect();

		static bool canUseGameWnd;	//ゲーム画面を操作中か

		static std::vector<std::pair<int, std::function<void()>>> activeEvents;	//実行できるイベント関数

		static void RemoveTriggerRect(TriggerRect* triggerRect);
		static void AddTriggerRect(TriggerRect* triggerRect);

		static void EventCheck();	//イベントトリガーチェック

		static void SetMenuList(MenuList* menuList);
		static MenuList* GetMenuList();

	private:
		static std::vector<TriggerRect*> triggerRects;	//反応する四角たち

		static TriggerRect* selectedTriggerRect;	//選択中のTriggerRect

		static MenuList* menuList;	//作られたメニューリスト
};

