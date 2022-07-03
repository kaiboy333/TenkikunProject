#include "ScrollRect.h"
#include "MyMath.h"
#include <string>

ScrollRect::ScrollRect(float startX, float startY, float width, float height, float scrollWidth, float scrollHeight, Window* parentWindow) : TriggerRect(startX, startY, width, height, parentWindow)
{
	this->scrollWidth = scrollWidth;
	this->scrollHeight = scrollHeight;
	startScrollX = startX;
	startScrollY = startY;

	//マウスホイールで動かしたら
	this->mouseWheelEvents.push_back([this]() {
		//スクロールの高さが表示可能高さよりも大きいなら
		if (this->scrollHeight > this->height) {
			//マウスホイールの回転値を取得
			float mouseWheelRote = Input::GetMouseWheelRoteValue();
			//OutputDebugString((std::to_string(mouseWheelRote) + std::string("\n")).c_str());

			//今のうちに前のスクロール位置を記憶
			float beforeStartScrollY = startScrollY;

			//指標になるスクロール座標をずらす
			startScrollY += mouseWheelRote * scrollSpeed;

			//範囲からはみ出さないように調整
			startScrollY = MyMath::Clamp(startScrollY, this->startY - (this->scrollHeight - this->height), this->startY);

			//今回の移動分を計算
			float deltaScrollY = startScrollY - beforeStartScrollY;

			for (TriggerRect* triggerRect : triggerRects) {
				//実際にY座標をずらす
				triggerRect->startY += deltaScrollY;
			}
			TriggerRectsActiveUpdate();	//有効化更新
		}
	});
}

void ScrollRect::AddToScrollRect(TriggerRect* triggerRect)
{
	//実際に座標をずらす
	triggerRect->startX += startScrollX - startX;
	triggerRect->startY += startScrollY - startY;

	//TriggerRectの有効範囲はスクロールのかぶる範囲である
	triggerRect->activeRect = Rect::GetCrossRect(triggerRect, this);

	//リストに追加
	triggerRects.push_back(triggerRect);
}

void ScrollRect::RemoveToScrollRect(TriggerRect* triggerRect)
{
	//リストから削除
	triggerRects.erase(remove(triggerRects.begin(), triggerRects.end(), triggerRect));

	triggerRect->activeRect = nullptr;	//無効化
}

void ScrollRect::TriggerRectsActiveUpdate()
{
	for (TriggerRect* triggerRect : triggerRects) {
		//TriggerRectの有効範囲はスクロールのかぶる範囲である
		triggerRect->activeRect = Rect::GetCrossRect(triggerRect, this);
	}
}
