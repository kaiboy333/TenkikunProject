#include "ScrollRect.h"
#include "MyMath.h"
#include <string>

ScrollRect::ScrollRect(float startX, float startY, float width, float height, float scrollWidth, float scrollHeight, Window* parentWindow) : TriggerRect(startX, startY, width, height, parentWindow)
{
	this->scrollWidth = scrollWidth;
	this->scrollHeight = scrollHeight;
	startScrollX = startX;
	startScrollY = startY;
	//deltaScrollX = 0;
	//deltaScrollY = 0;

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
			startScrollY -= mouseWheelRote * scrollSpeed;

			//範囲からはみ出さないように調整
			MyMath::Clamp(startScrollY, this->startY, this->startY + this->scrollHeight - this->height);

			//今回の移動分を計算
			float deltaScrollY = startScrollY - beforeStartScrollY;

			for (TriggerRect* triggerRect : triggerRects) {
				//実際にY座標をずらす
				triggerRect->startY -= deltaScrollY;

				//右端の位置がスクロールの枠から外れてるかでisOutを変える
				triggerRect->isOut = !IsPointIn(triggerRect->startX, triggerRect->startY);
			}
		}
	});
}

void ScrollRect::AddToScrollRect(TriggerRect* triggerRect)
{
	//実際に座標をずらす
	triggerRect->startX -= startScrollX - startX;
	triggerRect->startY -= startScrollY - startY;

	//右端の位置がスクロールの枠から外れてるかでisOutを変える
	triggerRect->isOut = !IsPointIn(triggerRect->startX, triggerRect->startY);

	//リストに追加
	triggerRects.push_back(triggerRect);
}

void ScrollRect::RemoveToScrollRect(TriggerRect* triggerRect)
{
	//リストから削除
	triggerRects.erase(remove(triggerRects.begin(), triggerRects.end(), triggerRect));
}
