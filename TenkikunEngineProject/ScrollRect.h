#pragma once
#include "TriggerRect.h"

class ScrollRect : public TriggerRect
{
	public:
		ScrollRect(float startX, float startY, float width, float height, float scrollWidth, float scrollHeight, Window* parentWindow);

		//float deltaScrollX, deltaScrollY;	//いままで動かしたマウスホイールの回転値
		float scrollWidth, scrollHeight;
		float startScrollX, startScrollY;

		float scrollSpeed = 10;

		void AddToScrollRect(TriggerRect* triggerRect);	//リストに追加
		void RemoveToScrollRect(TriggerRect* triggerRect);	//リストから削除

		void TriggerRectsActiveUpdate();	//TriggerRectsの有効化部分更新

	protected:
		std::vector<TriggerRect*> triggerRects;	//スクロールで動かすTriggerRect
};

