#pragma once

#include "Image.h"
#include <unordered_map>
#include <filesystem>

//�摜�Ǘ��N���X
class ImageManager
{
	public:
		//static std::unordered_map<std::filesystem::path, Image*> imagePathes;	//�摜�t�@�C���p�X����

		static int LoadAndGetImage(std::filesystem::path path);	//�摜�ɑΉ�����GraphicHandle��Ԃ��A�܂��͍쐬���ĕԂ��֐�

		static std::vector<int> LoadAndGetImages(std::vector<std::string> pathes);	//�摜�ɑΉ�����GraphicHandle��Ԃ��A�܂��͍쐬���ĕԂ��֐�(����)

		ImageManager();
};



