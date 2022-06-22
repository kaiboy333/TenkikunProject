#include "Window.h"
#include "WindowManager.h"

void Window::SetSelectedTriggerRect(TriggerRect* selectedTriggerRect)
{
	//if (this->selectedTriggerRect) {
	//	//前回の選択中のTriggerRectを選択しないようにして
	//	this->selectedTriggerRect->isSelected = false;
	//}
	//if (selectedTriggerRect) {
	//	//今回の選択中のTriggerRectを選択するようにする
	//	selectedTriggerRect->isSelected = true;
	//}

	//新しいのをセット
	this->selectedTriggerRect = selectedTriggerRect;
}

void Window::ClearSelectedTriggerRect()
{
	selectedTriggerRect = nullptr;
}

TriggerRect* Window::GetSelectedTriggerRect()
{
	return selectedTriggerRect;
}

void Window::RemoveTriggerRect(TriggerRect* triggerRect)
{
	removeTriggerRects.push_back(triggerRect);	//消すリストにいれる
}

void Window::AddTriggerRect(TriggerRect* triggerRect)
{
	addTriggerRects.push_back(triggerRect);	//追加するリストにいれる
}

Window::Window(float startX, float startY, float width, float height) : Rect(startX, startY, width, height)
{

}

void Window::Update()
{
	for (TriggerRect* removeTriggerRect : removeTriggerRects) {
		triggerRects.erase(remove(triggerRects.begin(), triggerRects.end(), removeTriggerRect));	//実際に削除
		removeTriggerRect->parentWindow = nullptr;	//TriggerRectから参照できないように
	}
	removeTriggerRects.clear();	//削除リストを初期化

	for (TriggerRect* addTriggerRect : addTriggerRects) {
		triggerRects.push_back(addTriggerRect);	//実際に追加
		addTriggerRect->parentWindow = this;	//TriggerRectから参照できるように
	}
	addTriggerRects.clear();	//追加リストを初期化
}

void Window::EventCheck()
{
	//TriggerRectのイベント発生
	for (TriggerRect* triggerRect : triggerRects) {
		triggerRect->CheckInput();	//イベントチェック
	}
}

void Window::Draw()
{
	//描画範囲制限
	SetDrawArea((int)startX, (int)startY, (int)(startX + width - 1), (int)(startY + height - 1));
	//白い四角を描画
	DrawBoxAA(startX, startY, startX + width - 1, startY + height - 1, GetColor(255, 255, 255), TRUE);
	//枠線を描画
	DrawBoxAA(startX, startY, startX + width - 1, startY + height - 1, GetColor(0, 0, 0), FALSE);

}
