#pragma once

#include "Rect.h"
#include "Component.h"
#include "DxLib.h"
#include "WindowManager.h"
#include "FontManager.h"
#include "CheckButton.h"
#include "SelectRect.h"

class TextRect;
class ComponentRect : public Rect
{
	public:
		Component* component;

		TextRect* nameRect = nullptr;

		ComponentRect(float startX, float startY, Component* component, int lineNum);

		virtual void Update() = 0;

		virtual void Draw();

		//virtual void RemoveAllTriggerRect() = 0;	//���g�������TriggerRect�����ׂč폜

		virtual void PreparationLibrate() override;

	protected:
		float rightStartDrawX = startX + width * 2 / 5;	//�E���̕����̕`��J�n�ʒuX

		const float mojiHeight = FontManager::systemFont->GetFontHeight();	//�����̍���

		static const float lineSpace;	//�s��

		int lineNum;	//�ǉ��ŕ`�悷��s�̐�

		float startDrawY;	//�`��J�n�ʒuY

		vector<TextBox*> textBoxes;		//���̓e�L�X�g�{�b�N�X
		vector<TextRect*> textRects;	//������\���{�b�N�X
		vector<CheckButton*> checkButtons;	//�`�F�b�N�{�b�N�X
		vector<SelectRect*> selectRects;	//�I�����{�b�N�X

		const float textBoxWidth = 40;
		const float textBoxHeight = FontManager::systemFont->GetFontHeight();

		void StartNewLine();	//���s����Ƃ��ɌĂ�
		float GetRightRectX(Rect* rect);	//Rect�̉E�[��X���擾
};

