#pragma once

#include <DxLib.h>
#include "FileIcon.h"
#include "MyMath.h"
#include "Info.h"

class Image : public Info
{
	public:
		Image(std::filesystem::path path);

		int GetGH();	//�O���t�B�b�N�n���h���擾(State�Ŏg��)

		float GetWidth();	//�����擾
		float GetHeight();	//�c���擾

		void SetAlpha(int alpha);
		int GetAlpha();

		std::filesystem::path GetPath();

	private:
		int gh = -1;

		float width, height;	//�����A�c��

		int alpha = 255;	//�摜�̃A���t�@�l

		std::filesystem::path path;	//�摜�̃p�X
};

