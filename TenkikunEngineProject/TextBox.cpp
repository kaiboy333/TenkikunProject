#include "TextBox.h"
#include "FontManager.h"
#include "Debug.h"
#include "WindowManager.h"
//#include "Window.h"

TextBox::TextBox(float startX, float startY, float width, float height, bool canChange, string text, InputType inputType) : TriggerRect(startX, startY, width, height)
{
	this->text = text;	//�e�L�X�g�Z�b�g
	this->inputType = inputType;	//���̓^�C�v�Z�b�g
	this->canChange = canChange;	//�����͕ς����邩

	//�N���b�N������
	mouseClickDownEvents.push_back(std::make_pair(1, [this] {
		//�ύX�\�Ȃ�
		if (this->canChange) {
			//���͒��ł͂Ȃ��Ȃ�
			if (!GetIsSelected()) {
				bool isTypeNum = (this->inputType == InputType::Number);

				ih = MakeKeyInput(MAX_LEN, FALSE, FALSE, FALSE);	//InputHandle�쐬
				SetActiveKeyInput(ih);	//���͂��\�ɂ���
				SetKeyInputString(this->text.c_str(), ih);	//���͒��̕����̒��Ɋ��ɂ���text�������
				WindowManager::SetSelectedTriggerRect(this);	//���g��I��Ώۂɂ���
			}
		}
	}));

	//�G���^�[����������
	pushEnterEvents.push_back(std::make_pair(1, [this]() {
		//���͒��������Ȃ�
		if (GetIsSelected()) {
			TCHAR strBuf[MAX_LEN + 1] = {};
			GetKeyInputString(strBuf, ih);
			//�󔒂ł͂Ȃ��Ȃ�
			if (std::string(strBuf) != "") {
				this->text = strBuf;	//���͂����������Z�b�g
			}

			WindowManager::SetSelectedTriggerRect(nullptr);	//���g��I��Ώۂ���O��
			DxLib::DeleteKeyInput(ih);	//InputHandle�폜
		}
	}));
}

void TextBox::Draw()
{
	RECT beforeDrawRect;
	//�`��̈���L��
	GetDrawArea(&beforeDrawRect);

	if (canChange) {
		//�}�E�X������Ă�����
		if (isOn) {
			//�l�p�̕`��
			DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(200, 200, 200), TRUE);
		}
		DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(0, 0, 0), FALSE);	//�g�̕`��
	}

	SetKeyInputStringColor(GetColor(0, 0, 0), GetColor(50, 0, 0), GetColor(200, 200, 200), GetColor(0, 0, 50), GetColor(0, 0, 0)
		, GetColor(0, 0, 255), GetColor(0, 0, 100), GetColor(0, 0, 0), GetColor(0, 0, 0), GetColor(0, 0, 0), GetColor(0, 0, 0)
		, GetColor(200, 200, 200), GetColor(0, 0, 0), GetColor(0, 0, 200), GetColor(100, 100, 0), GetColor(0, 0, 0), GetColor(0, 0, 0)
	);

	//DrawKeyInputModeString(0, 0);	//���̓��[�h�̕`��

	TCHAR strBuf[MAX_LEN + 1] = "";
	GetKeyInputString(strBuf, ih);
	//���͒��ł͂Ȃ��Ȃ�
	if (!GetIsSelected()) {
		//�L�����͈͓��Ȃ�
		if (activeRect) {
			//�`�搧��
			SetDrawArea((int)activeRect->startX, (int)activeRect->startY, (int)(activeRect->startX + activeRect->width), (int)(activeRect->startY + activeRect->height));
			//�ϊ���̕�����`��
			DrawStringFToHandle(startX, startY, text.c_str(), GetColor(0, 0, 0), FontManager::systemFont->GetFH());
			//�O��̕`��̈�ɖ߂�
			SetDrawArea(beforeDrawRect.left, beforeDrawRect.top, beforeDrawRect.right, beforeDrawRect.bottom);
		}
	}
	else {
		if (canChange) {
			DrawBoxAA(startX, startY, startX + FontManager::systemFont->GetFontWidth(strBuf), startY + FontManager::systemFont->GetFontHeight(), GetColor(30, 144, 255), TRUE);
		}
		DrawStringFToHandle(startX, startY, strBuf, GetColor(0, 0, 0), FontManager::systemFont->GetFH());	//���͒��̕�����̕`��
	}
}

void TextBox::SetText(string text)
{
	this->text = text;
}

string TextBox::GetText()
{
	return text;
}