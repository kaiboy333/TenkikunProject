#pragma once

#include <DxLib.h>
#include "FileIcon.h"
#include "MyMath.h"
#include "Info.h"

class Info;
class Image : public Info
{
	public:
		Image(std::filesystem::path path);

		int GetGH();	//�O���t�B�b�N�n���h���擾(State�Ŏg��)

		float GetWidth();	//�����擾
		float GetHeight();	//�c���擾

		void SetAlpha(int alpha);
		int GetAlpha();

	private:
		int gh = -1;

		float width = 0, height = 0;	//�����A�c��

		int alpha = 255;	//�摜�̃A���t�@�l
};

