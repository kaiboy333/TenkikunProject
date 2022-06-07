#include "TextRect.h"
#include "DxLib.h"

TextRect::TextRect(float startX, float startY, string text) : Rect(startX, startY, (float)GetDrawStringWidth(text.c_str(), (int)(text.length())), (float)GetFontLineSpace())
{
	this->text = text;
}

void TextRect::SetText(string text)
{
	//名前セット
	this->text = text;
	//それによる幅、高さ更新
	width = (float)GetDrawStringWidth(text.c_str(), (int)text.length());
	height = (float)GetFontLineSpace();
}

string TextRect::GetText()
{
	return text;
}

void TextRect::Draw()
{
	DrawStringF(startX, startY, text.c_str(), GetColor(0, 0, 0));	//文字描画
}
