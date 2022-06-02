#pragma once

#include "Window.h"
#include "GameWindow.h"
#include "HierarchyWindow.h"
#include "InspectorWindow.h"

class GameWindow;
class HierarchyWindow;
class WindowManager
{
	public:
		static GameWindow* gameWindow;
		static HierarchyWindow* hierarchyWindow;
		static InspectorWindow* inspectorWindow;

		static std::vector<TriggerRect*> triggerRects;	//反応する四角たち

		static void Update();	//画面のマウスチェック
		static void Draw();

		static void SetSelectedTriggerRect(TriggerRect* selectedTriggerRect);

	private:
		static TriggerRect* selectedTriggerRect;	//選択中のTriggerRect
};

