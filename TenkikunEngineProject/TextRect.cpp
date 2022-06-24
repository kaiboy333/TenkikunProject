#include "TextRect.h"
#include "DxLib.h"

TextRect::TextRect(float startX, float startY, std::string text) : Rect(startX, startY, (float)GetDrawStringWidth(text.c_str(), (int)(text.length())), (float)GetFontLineSpace())
{
	this->text = text;
}

void TextRect::SetText(std::string text)
{
	//���O�Z�b�g
	this->text = text;
	//����ɂ�镝�A�����X�V
	width = (float)GetDrawStringWidth(text.c_str(), (int)text.length());
	height = (float)GetFontLineSpace();
}

std::string TextRect::GetText()
{
	return text;
}

void TextRect::Draw()
{
	DrawStringF(startX, startY, text.c_str(), GetColor(0, 0, 0));	//�����`��
}
