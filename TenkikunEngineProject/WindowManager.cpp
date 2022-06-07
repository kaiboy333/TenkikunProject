#include "WindowManager.h"

void WindowManager::Draw()
{
	gameWindow->Draw();	//ゲーム画面の描画
	hierarchyWindow->Draw();	//ヒエラルキーウィンドウの描画
	inspectorWindow->Draw();	//インスペクターウィンドウの描画
}

void WindowManager::Update()
{
	gameWindow->Update();	//ゲーム画面の更新
	hierarchyWindow->Update();	//ヒエラルキーウィンドウの更新
	inspectorWindow->Update();	//インスペクターウィンドウの更新

	//TriggerRectのイベント発生
	for (TriggerRect* triggerRect : triggerRects) {
		triggerRect->CheckInput();	//イベントチェック
	}
	for (TriggerRect* removeTriggerRect : removeTriggerRects) {
		triggerRects.erase(remove(triggerRects.begin(), triggerRects.end(), removeTriggerRect));	//実際に削除
	}
	removeTriggerRects.clear();	//削除リストを初期化
	for (TriggerRect* addTriggerRect : addTriggerRects) {
		triggerRects.push_back(addTriggerRect);	//実際に追加
	}
	addTriggerRects.clear();	//追加リストを初期化
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

TriggerRect* WindowManager::GetSelectedTriggerRect()
{
	return selectedTriggerRect;
}

void WindowManager::AddTriggerRect(TriggerRect* triggerRect) {
	WindowManager::addTriggerRects.push_back(triggerRect);	//追加するリストにいれる
}

void WindowManager::RemoveTriggerRect(TriggerRect* triggerRect) {
	WindowManager::removeTriggerRects.push_back(triggerRect);	//消すリストにいれる
}

std::vector<TriggerRect*> WindowManager::triggerRects;
std::vector<TriggerRect*> WindowManager::removeTriggerRects;
std::vector<TriggerRect*> WindowManager::addTriggerRects;

TriggerRect* WindowManager::selectedTriggerRect;

GameWindow* WindowManager::gameWindow = new GameWindow();
HierarchyWindow* WindowManager::hierarchyWindow = new HierarchyWindow();
InspectorWindow* WindowManager::inspectorWindow = new InspectorWindow();

