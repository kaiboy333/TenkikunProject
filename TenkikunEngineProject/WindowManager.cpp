#include "WindowManager.h"

void WindowManager::Draw()
{
	gameWindow->Draw();	//ゲーム画面の描画
	hierarchyWindow->Draw();	//ヒエラルキーウィンドウの描画
	inspectorWindow->Draw();	//インスペクターウィンドウの描画
}

void WindowManager::Update()
{
	//TriggerRectのイベント発生
	for (TriggerRect* triggerRect : triggerRects) {
		triggerRect->CheckInput();
	}
}

void WindowManager::SetSelectedTriggerRect(TriggerRect* selectedTriggerRect)
{
	if (WindowManager::selectedTriggerRect) {
		//前回の選択中のTriggerRectを選択しないようにして
		WindowManager::selectedTriggerRect->isSelected = false;
	}
	if (selectedTriggerRect) {
		//今回の選択中のTriggerRectを選択するようにする
		selectedTriggerRect->isSelected = true;
	}

	//新しいのをセット
	WindowManager::selectedTriggerRect = selectedTriggerRect;
}

std::vector<TriggerRect*> WindowManager::triggerRects;
TriggerRect* WindowManager::selectedTriggerRect;

GameWindow* WindowManager::gameWindow = new GameWindow();
HierarchyWindow* WindowManager::hierarchyWindow = new HierarchyWindow();
InspectorWindow* WindowManager::inspectorWindow = new InspectorWindow();

