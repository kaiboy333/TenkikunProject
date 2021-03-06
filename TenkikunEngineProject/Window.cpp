#include "Window.h"
#include "WindowManager.h"

void Window::SetSelectedTriggerRect(TriggerRect* selectedTriggerRect)
{
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
	//removeTriggerRects.push_back(triggerRect);	//消すリストにいれる

	//何か入っているなら
	if (triggerRects.size() != 0) {
		//要素が存在するなら
		if (*std::find(triggerRects.begin(), triggerRects.end(), triggerRect) == triggerRect) {
			triggerRects.erase(remove(triggerRects.begin(), triggerRects.end(), triggerRect));	//実際に削除
			triggerRect->parentWindow = nullptr;	//TriggerRectから参照できないように
		}
	}
}

void Window::AddTriggerRect(TriggerRect* triggerRect)
{
	//addTriggerRects.push_back(triggerRect);	//追加するリストにいれる

	triggerRects.push_back(triggerRect);	//実際に追加
	triggerRect->parentWindow = this;	//TriggerRectから参照できるように
}

Window::Window(float startX, float startY, float width, float height) : Rect(startX, startY, width, height)
{

}

void Window::Update()
{
	//for (TriggerRect* removeTriggerRect : removeTriggerRects) {
	//	//何か入っているなら
	//	if (triggerRects.size() != 0) {
	//		//要素が存在するなら
	//		if (*std::find(triggerRects.begin(), triggerRects.end(), removeTriggerRect) == removeTriggerRect) {
	//			triggerRects.erase(remove(triggerRects.begin(), triggerRects.end(), removeTriggerRect));	//実際に削除
	//			removeTriggerRect->parentWindow = nullptr;	//TriggerRectから参照できないように
	//		}
	//	}
	//}
	//removeTriggerRects.clear();	//削除リストを初期化

	//for (TriggerRect* addTriggerRect : addTriggerRects) {
	//	triggerRects.push_back(addTriggerRect);	//実際に追加
	//	addTriggerRect->parentWindow = this;	//TriggerRectから参照できるように
	//}
	//addTriggerRects.clear();	//追加リストを初期化
}

void Window::EventCheck()
{
	//TriggerRectのイベント発生
	for (TriggerRect* triggerRect : triggerRects) {
		triggerRect->CheckInput();	//イベントチェック
	}

	if ((int)activeEvents.size() != 0) {
		//昇順にソート
		std::sort(activeEvents.begin(), activeEvents.end(), [](const std::pair<int, std::function<void()>>& a, const std::pair<int, std::function<void()>>& b)
		{
			return a.first > b.first;
		});

		int activeEventNo = activeEvents.begin()->first;	//実際に実行する番号を記憶

		for (std::pair<int, std::function<void()>> activeEvent : activeEvents) {
			//番号が同じだったなら
			if (activeEvent.first == activeEventNo) {
				activeEvent.second();	//イベントを実行する
			}
			else {
				//終わり
				break;
			}
		}
		activeEvents.clear();	//リストを初期化
	}
}

void Window::Draw()
{
	//描画範囲制限
	SetDrawArea((int)startX, (int)startY, (int)(startX + width), (int)(startY + height));
	//画像のアルファ値設定
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	//白い四角を描画
	DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(255, 255, 255), TRUE);
	//枠線を描画
	DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(0, 0, 0), FALSE);

}