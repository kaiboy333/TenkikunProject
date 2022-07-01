#include "Font.h"
#include "DxLib.h"

Font::Font(const char* fontName, int size, int thick, int fontType)
{
	fh = CreateFontToHandle(fontName, size, thick, fontType);

	if (fontName) {
		this->fontName = fontName;
	}
	this->size = size;
	this->thick = thick;
	this->fontType = fontType;
}

int Font::GetFH()
{
	return fh;
}

float Font::GetFontWidth(std::string str)
{
	return GetDrawStringWidthToHandle(str.c_str(), str.length(), fh);
}

float Font::GetFontHeight()
{
	return GetFontSizeToHandle(fh);
}
