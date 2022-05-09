#pragma once

#include <iostream>
#include "ImageManager.h"
#include <DxLib.h>

class Image
{
	public:
		Image(std::string path);

		int* GetGH();	//�O���t�B�b�N�n���h���擾(State�Ŏg��)

		float GetWidth();	//�����擾
		float GetHeight();	//�c���擾

	private:
		int* gh = nullptr;

		float width, height;	//�����A�c��

		std::string path;	//�摜�̃p�X
};

inline Image::Image(std::string path)
{
	this->path = path;	//�p�X������
	this->gh = ImageManager::Instance()->LoadAndGetImage(path);	//�摜�ǂݍ���
	GetGraphSizeF(*gh, &width, &height);	//�摜�T�C�Y�擾
}

inline int* Image::GetGH()
{
	return gh;
}

inline float Image::GetWidth()
{
	return width;
}

inline float Image::GetHeight()
{
	return height;
}


