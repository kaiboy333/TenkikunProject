#pragma once

#include <iostream>
#include <unordered_map>

//�摜�Ǘ��N���X
class ImageManager
{
	public:
		static ImageManager* Instance();	//�������疈��C���X�^���X���Ă�

		static void Destroy();	//�C���X�^���X���폜(���)

		std::unordered_map<std::string, int*> ghs;	//�摜�t�@�C���ɑΉ�����GraphicHandle���L�^��������

		int* LoadAndGetImage(std::string path);	//�摜�ɑΉ�����GraphicHandle��Ԃ��A�܂��͍쐬���ĕԂ��֐�

		std::vector<int*> LoadAndGetImages(std::vector<std::string> pathes);	//�摜�ɑΉ�����GraphicHandle��Ԃ��A�܂��͍쐬���ĕԂ��֐�(����)

	private:
		ImageManager();	//�C���X�^���X�𕁒ʂɂ͐��������Ȃ�

		static ImageManager* instance;	//����������̃C���X�^���X
};



