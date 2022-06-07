#include "TextBox.h"

TextBox::TextBox(float startX, float startY, float width, float height, string text) : TriggerRect(startX, startY, width, height)
{
	this->text = text;	//�e�L�X�g�Z�b�g

	//�N���b�N������
	mouseClickDownEvents.push_back([this] {
		//InitKeyInput();	//���͏�����
		ih = MakeKeyInput(MAX_LEN, FALSE, FALSE, FALSE);	//InputHandle�쐬
		SetActiveKeyInput(ih);	//���͂��\�ɂ���
		SetKeyInputString(this->text.c_str(), ih);	//���͒��̕����̒��Ɋ��ɂ���text�������
		isInputing = true;	//���͏�ԃt���O�I��
	});

	//�G���^�[����������
	pushEnterEvents.push_back([this]() {
		//���͒��������Ȃ�
		if (isInputing) {
			TCHAR strBuf[MAX_LEN + 1] = "";
			GetKeyInputString(strBuf, ih);
			//�󔒂ł͂Ȃ��Ȃ�
			if (strBuf != "") {
				this->text = string(strBuf);	//���͂����������Z�b�g
			}
			else {

			}

			isInputing = false;	//���͏�ԃt���O�I�t
			InitKeyInput();	//���͂�s��(������)
		}
	});
}

void TextBox::Draw()
{
	DrawBoxAA(startX, startY, startX + width - 1, startY + height - 1, GetColor(0, 0, 0), FALSE);	//�g�̕`��

	SetKeyInputStringColor(GetColor(0, 0, 0), GetColor(50, 0, 0), GetColor(200, 200, 200), GetColor(0, 0, 50), GetColor(100, 0, 0)
		, GetColor(200, 200, 200), GetColor(0, 0, 100), GetColor(0, 0, 0), GetColor(200, 200, 200), GetColor(150, 0, 0), GetColor(150, 0, 0)
		, GetColor(200, 0, 0), GetColor(0, 0, 0), GetColor(0, 0, 200), GetColor(100, 100, 0), GetColor(0, 0, 0), GetColor(0, 0, 0)
	);

	//DrawKeyInputModeString(0, 0);	//���̓��[�h�̕`��

	TCHAR strBuf[MAX_LEN + 1] = "";
	GetKeyInputString(strBuf, ih);
	//SetDrawArea(startX, startY, startX + width - 1, startY + height - 1);
	//���͒��ł͂Ȃ��Ȃ�
	if (!isInputing) {
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