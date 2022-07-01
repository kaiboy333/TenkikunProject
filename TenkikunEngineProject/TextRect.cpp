#include "TextRect.h"
#include "DxLib.h"
#include "FontManager.h"

TextRect::TextRect(float startX, float startY, std::string text) : Rect(startX, startY, FontManager::systemFont->GetFontWidth(text), FontManager::systemFont->GetFontHeight())
{
	this->text = text;
}

void TextRect::SetText(std::string text)
{
	//名前セット
	this->text = text;
	//それによる幅、高さ更新
	width = FontManager::systemFont->GetFontWidth(text);
	height = FontManager::systemFont->GetFontHeight();
}

std::string TextRect::GetText()
{
	return text;
}

void TextRect::Draw()
{
	//SetDrawArea(startX, startY, startX + width, startY + height);
	//文字描画
	DrawStringFToHandle(startX, startY, text.c_str(), GetColor(0, 0, 0), FontManager::systemFont->GetFH());
}
