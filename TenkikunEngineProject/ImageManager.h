#pragma once

#include <iostream>
#include <unordered_map>

//�摜�Ǘ��N���X
class ImageManager
{
	public:
		//static std::unordered_map<std::string, int*> ghs;	//�摜�t�@�C���ɑΉ�����GraphicHandle���L�^��������

		static int LoadAndGetImage(std::string path);	//�摜�ɑΉ�����GraphicHandle��Ԃ��A�܂��͍쐬���ĕԂ��֐�

		static std::vector<int> LoadAndGetImages(std::vector<std::string> pathes);	//�摜�ɑΉ�����GraphicHandle��Ԃ��A�܂��͍쐬���ĕԂ��֐�(����)

		ImageManager();
};



