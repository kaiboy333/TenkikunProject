#pragma once

#include "DxLib.h"
#include "TriggerRect.h"
#include <vector>

class TriggerRect;
class Window : public TriggerRect
{
	public:
		void SetSelectedTriggerRect(TriggerRect* selectedTriggerRect);
		TriggerRect* GetSelectedTriggerRect();

		void RemoveTriggerRect(TriggerRect* triggerRect);
		void AddTriggerRect(TriggerRect* triggerRect);

		Window(float startX, float startY, float width, float height);

		virtual void Update() = 0;

		void EventUpdate();	//イベントトリガーチェック

		virtual void Draw();	//描画

	private:
		TriggerRect* selectedTriggerRect = nullptr;	//選択中のTriggerRect

		std::vector<TriggerRect*> triggerRects;	//反応する四角たち
		std::vector<TriggerRect*> removeTriggerRects;	//反応する四角たち(消すやつ)
		std::vector<TriggerRect*> addTriggerRects;	//反応する四角たち(追加するやつ)
};

