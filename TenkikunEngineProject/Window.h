#pragma once

#include "DxLib.h"
#include <vector>
#include "TriggerRect.h"

class TriggerRect;
class Window : public Rect
{
	public:
		void SetSelectedTriggerRect(TriggerRect* selectedTriggerRect);	//�w���TriggerRect��I�����ꂽ��Ԃɂ���(�O�͉̂���)
		void ClearSelectedTriggerRect();	//���ׂĂ̑I�����ꂽ��Ԃ�TriggerRect����������

		TriggerRect* GetSelectedTriggerRect();

		void RemoveTriggerRect(TriggerRect* triggerRect);
		void AddTriggerRect(TriggerRect* triggerRect);

		Window(float startX, float startY, float width, float height);

		virtual void Update();

		bool EventCheck();	//�C�x���g�g���K�[�`�F�b�N

		virtual void Draw();	//�`��

	private:
		TriggerRect* selectedTriggerRect = nullptr;	//�I�𒆂�TriggerRect

		std::vector<TriggerRect*> triggerRects;	//��������l�p����
		std::vector<TriggerRect*> removeTriggerRects;	//��������l�p����(�������)
		std::vector<TriggerRect*> addTriggerRects;	//��������l�p����(�ǉ�������)
};

