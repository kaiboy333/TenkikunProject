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

		static Window* activeTrigggerWindow;

		static void Update();	//画面のマウスチェック
		static void Draw();

		static vector<Window*> GetWindows();	//現在あるすべてのウィンドウを取得

		//static void SetSelectedTriggerRect(TriggerRect* selectedTriggerRect);
		//static TriggerRect* GetSelectedTriggerRect();

		//static void RemoveTriggerRect(TriggerRect* triggerRect);
		//static void AddTriggerRect(TriggerRect* triggerRect);

	private:
		//static TriggerRect* selectedTriggerRect;	//選択中のTriggerRect

		//static std::vector<TriggerRect*> triggerRects;	//反応する四角たち
		//static std::vector<TriggerRect*> removeTriggerRects;	//反応する四角たち(消すやつ)
		//static std::vector<TriggerRect*> addTriggerRects;	//反応する四角たち(追加するやつ)
};

