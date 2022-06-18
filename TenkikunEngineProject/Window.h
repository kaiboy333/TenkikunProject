#pragma once

#include "DxLib.h"
#include <vector>
#include "TriggerRect.h"

class TriggerRect;
class Window : public Rect
{
	public:
		void SetSelectedTriggerRect(TriggerRect* selectedTriggerRect);	//指定のTriggerRectを選択された状態にする(前のは解除)
		void ClearSelectedTriggerRect();	//すべての選択された状態のTriggerRectを解除する

		TriggerRect* GetSelectedTriggerRect();

		void RemoveTriggerRect(TriggerRect* triggerRect);
		void AddTriggerRect(TriggerRect* triggerRect);

		Window(float startX, float startY, float width, float height);

		virtual void Update();

		bool EventCheck();	//イベントトリガーチェック

		virtual void Draw();	//描画

	private:
		TriggerRect* selectedTriggerRect = nullptr;	//選択中のTriggerRect

		std::vector<TriggerRect*> triggerRects;	//反応する四角たち
		std::vector<TriggerRect*> removeTriggerRects;	//反応する四角たち(消すやつ)
		std::vector<TriggerRect*> addTriggerRects;	//反応する四角たち(追加するやつ)
};

