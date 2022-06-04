#pragma once

#include "Rect.h"
#include "Component.h"
#include "DxLib.h"

class ComponentRect : public Rect
{
	public:
		Component* component;

		ComponentRect(float startX, float startY, Component* component, int lineNum);

		virtual void Draw();

	protected:
		const float rightStartDrawX = startX + width * 2 / 3;	//�E���̕����̕`��J�n�ʒuX

		const float mojiHeight = (float)GetFontLineSpace();	//�����̍���

		const float lineSpace = 5;	//�s��

		int lineNum;	//�ǉ��ŕ`�悷��s�̐�

		float startDrawY;	//�`��J�n�ʒuY

		void StartNewLine();	//���s����Ƃ��ɌĂ�
};

