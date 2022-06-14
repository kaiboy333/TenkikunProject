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

		void EventUpdate();	//�C�x���g�g���K�[�`�F�b�N

		virtual void Draw();	//�`��

	private:
		TriggerRect* selectedTriggerRect = nullptr;	//�I�𒆂�TriggerRect

		std::vector<TriggerRect*> triggerRects;	//��������l�p����
		std::vector<TriggerRect*> removeTriggerRects;	//��������l�p����(�������)
		std::vector<TriggerRect*> addTriggerRects;	//��������l�p����(�ǉ�������)
};

