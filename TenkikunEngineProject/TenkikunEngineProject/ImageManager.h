#pragma once

#include <iostream>
#include "DxLib.h"
#include <unordered_map>

//�摜�Ǘ��N���X
class ImageManager
{
	public:
		static std::unordered_map<std::string, int*> ghs;	//�摜�t�@�C���ɑΉ�����GraphicHandle���L�^��������

		static int* LoadImage(std::string path);	//�摜�ɑΉ�����GraphicHandle��Ԃ��A�܂��͍쐬���ĕԂ��֐�
};

