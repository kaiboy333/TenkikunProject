#pragma once
#include "Component.h"
#include "DxLib.h"
#include <iostream>

class Image :  public Component
{
	public:
		bool isFlipX = FALSE;
		bool isFlipY = FALSE;

		void Draw();	//�摜��`��

		void SetImage(std::string path);	//�t�@�C���p�X����GraphicHandle���Z�b�g
		void SetGH(int* gh);	//GraphicHandle���Z�b�g

		inline void SetGH(int* gh) {
			this->gh = gh;
		}
	private:
		int* gh = 0;	//�O���t�B�b�N�n���h��
};

