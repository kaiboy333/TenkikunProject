#include "WindowManager.h"

void WindowManager::Draw()
{
	gameWindow->Draw();	//ゲーム画面の描画
	hierarchyWindow->Draw();	//ヒエラルキーウィンドウの描画
	inspectorWindow->Draw();	//インスペクターウィンドウの描画
}

void WindowManager::Update()
{
	for (Window* window : GetWindows()) {
		window->Update();

		window->EventUpdate();
	}
}

vector<Window*> WindowManager::GetWindows()
{
	vector<Window*> windows;

	if (gameWindow && hierarchyWindow && inspectorWindow) {
		windows.push_back(gameWindow);
		windows.push_back(hierarchyWindow);
		windows.push_back(inspectorWindow);
	}

	return windows;
}

//void WindowManager::SetSelectedTriggerRect(TriggerRect* selectedTriggerRect)
//{
//	if (WindowManager::selectedTriggerRect) {
//		//前回の選択中のTriggerRectを選択しないようにして
//		WindowManager::selectedTriggerRect->isSelected = false;
//	}
//	if (selectedTriggerRect) {
//		//今回の選択中のTriggerRectを選択するようにする
//		selectedTriggerRect->isSelected = true;
//	}
//
//	//新しいのをセット
//	WindowManager::selectedTriggerRect = selectedTriggerRect;
//}

//TriggerRect* WindowManager::GetSelectedTriggerRect()
//{
//	return selectedTriggerRect;
//}
//
//void WindowManager::AddTriggerRect(TriggerRect* triggerRect) {
//	WindowManager::addTriggerRects.push_back(triggerRect);	//追加するリストにいれる
//}
//
//void WindowManager::RemoveTriggerRect(TriggerRect* triggerRect) {
//	WindowManager::removeTriggerRects.push_back(triggerRect);	//消すリストにいれる
//}
//
//std::vector<TriggerRect*> WindowManager::triggerRects;
//std::vector<TriggerRect*> WindowManager::removeTriggerRects;
//std::vector<TriggerRect*> WindowManager::addTriggerRects;
//
//TriggerRect* WindowManager::selectedTriggerRect;

GameWindow* WindowManager::gameWindow = new GameWindow();
HierarchyWindow* WindowManager::hierarchyWindow = new HierarchyWindow();
InspectorWindow* WindowManager::inspectorWindow = new InspectorWindow();

Window* WindowManager::activeTrigggerWindow = WindowManager::gameWindow;	//初期はゲーム画面

