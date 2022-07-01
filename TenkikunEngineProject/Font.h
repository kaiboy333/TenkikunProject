#pragma once
#include <string>
class Font
{
	public:
		Font(const char* fontName, int size, int thick, int fontType);

		int GetFH();	//�t�H���g�n���h���擾

		float GetFontWidth(std::string str);	//����str�ł̕����擾
		float GetFontHeight();	//�����̍������擾

	private:
		std::string fontName;
		int size;
		int thick;
		int fontType;

		int fh;	//�t�H���g�n���h��
};

