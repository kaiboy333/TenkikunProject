#include "TextBox.h"
//#include "Window.h"

TextBox::TextBox(float startX, float startY, float width, float height, InputType inputType, string text) : TriggerRect(startX, startY, width, height)
{
	this->text = text;	//�e�L�X�g�Z�b�g
	this->inputType = inputType;	//���̓^�C�v�Z�b�g

	//�N���b�N������
	mouseClickDownEvents.push_back([this] {
		//���͒��ł͂Ȃ��Ȃ�
		if (!GetIsSelected()) {
			bool isTypeNum = (this->inputType == InputType::Number);

			ih = MakeKeyInput(MAX_LEN, FALSE, FALSE, FALSE);	//InputHandle�쐬
			SetActiveKeyInput(ih);	//���͂��\�ɂ���
			SetKeyInputString(this->text.c_str(), ih);	//���͒��̕����̒��Ɋ��ɂ���text�������
			parentWindow->SetSelectedTriggerRect(this);	//���g��I��Ώۂɂ���
		}
	});

	//�G���^�[����������
	pushEnterEvents.push_back([this]() {
		//���͒��������Ȃ�
		if (GetIsSelected()) {
			TCHAR strBuf[MAX_LEN + 1] = {};
			GetKeyInputString(strBuf, ih);
			//�󔒂ł͂Ȃ��Ȃ�
			if (strBuf != "") {
				this->text = string(strBuf);	//���͂����������Z�b�g
			}

			parentWindow->SetSelectedTriggerRect(nullptr);	//���g��I��Ώۂ���O��
			DxLib::DeleteKeyInput(ih);	//InputHandle�폜
		}
	});
}

void TextBox::Draw()
{
	SetDrawArea(parentWindow->startX, parentWindow->startY, parentWindow->startX + parentWindow->width - 1, parentWindow->startY + parentWindow->height - 1);

	//�}�E�X������Ă�����
	if (isOn) {
		DrawBoxAA(startX, startY, startX + width - 1, startY + height - 1, GetColor(220, 220, 220), TRUE);
	}
	DrawBoxAA(startX, startY, startX + width - 1, startY + height - 1, GetColor(0, 0, 0), FALSE);	//�g�̕`��

	SetKeyInputStringColor(GetColor(0, 0, 0), GetColor(50, 0, 0), GetColor(200, 200, 200), GetColor(0, 0, 50), GetColor(0, 0, 0)
		, GetColor(0, 0, 255), GetColor(0, 0, 100), GetColor(0, 0, 0), GetColor(0, 0, 0), GetColor(0, 0, 0), GetColor(0, 0, 0)
		, GetColor(200, 200, 200), GetColor(0, 0, 0), GetColor(0, 0, 200), GetColor(100, 100, 0), GetColor(0, 0, 0), GetColor(0, 0, 0)
	);

	//DrawKeyInputModeString(0, 0);	//���̓��[�h�̕`��

	TCHAR strBuf[MAX_LEN + 1] = "";
	GetKeyInputString(strBuf, ih);
	//���͒��ł͂Ȃ��Ȃ�
	if (!GetIsSelected()) {
		SetDrawArea(startX, startY, startX + width - 1, startY + height - 1);
		DrawStringF(startX, startY, text.c_str(), GetColor(0, 0, 0));	//�ϊ���̕�����`��
	}
	else {
		DrawBoxAA(startX, startY, startX + (float)GetDrawStringWidth(strBuf, strlen(strBuf)), startY + (float)GetFontLineSpace(), GetColor(200, 200, 200), TRUE);
		DrawKeyInputString((int)startX, (int)startY, ih);	//���͒��̕�����̕`��
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