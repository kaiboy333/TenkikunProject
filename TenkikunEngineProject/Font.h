#pragma once
#include <string>
class Font
{
	public:
		Font(const char* fontName, int size, int thick, int fontType);

		int GetFH();	//フォントハンドル取得

		float GetFontWidth(std::string str);	//文字strでの幅を取得
		float GetFontHeight();	//文字の高さを取得

	private:
		std::string fontName;
		int size;
		int thick;
		int fontType;

		int fh;	//フォントハンドル
};

