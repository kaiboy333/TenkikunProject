#include "TextButton.h"
#include "FontManager.h"

TextButton::TextButton(float startX, float startY, float width, float height, int eventNo, std::string text) : TriggerRect(startX, startY, width, height, eventNo)
{
    this->text = text;
}

void TextButton::Draw()
{
    if (!isActive)
        return;

	RECT beforeDrawRect;
	//�`��̈���L��
	GetDrawArea(&beforeDrawRect);

	//�}�E�X������Ă�����
	if (GetIsTopOn()) {
		//�l�p�̕`��
		DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(200, 200, 200), TRUE);
	}
	DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(0, 0, 0), FALSE);	//�g�̕`��

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

void TextButton::SetText(std::string text)
{
    this->text = text;
}

std::string TextButton::GetText()
{
    return text;
}

void TextButton::PreparationLibrate()
{
    //���g�̉������
    TriggerRect::PreparationLibrate();
}
