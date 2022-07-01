#pragma once
#include "TriggerRect.h"

class ScrollRect : public TriggerRect
{
	public:
		ScrollRect(float startX, float startY, float width, float height, float scrollWidth, float scrollHeight, Window* parentWindow);

		//float deltaScrollX, deltaScrollY;	//���܂܂œ��������}�E�X�z�C�[���̉�]�l
		float scrollWidth, scrollHeight;
		float startScrollX, startScrollY;

		float scrollSpeed = 10;

		void AddToScrollRect(TriggerRect* triggerRect);	//���X�g�ɒǉ�
		void RemoveToScrollRect(TriggerRect* triggerRect);	//���X�g����폜

		void TriggerRectsActiveUpdate();	//TriggerRects�̗L���������X�V

	protected:
		std::vector<TriggerRect*> triggerRects;	//�X�N���[���œ�����TriggerRect
};

