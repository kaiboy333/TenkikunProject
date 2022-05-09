#pragma once

#include <iostream>
#include <map>
#include "Image.h"
#include <vector>

class Animation
{
	public:
		std::map<int, Image*> frameAndImages;	//�摜�Ƃ��ꂪ����Frame��

		bool isLoop = true;

		Animation(std::vector<Image*> images, int framePerChange);
};

inline Animation::Animation(std::vector<Image*> images, int framePerChange = 5)
{
	int length = static_cast<int>(images.size());
	for (int i = 0; i < length; i++) {
		//framePerChange�ÂJ���ē���Ă���
		frameAndImages.insert(std::make_pair(framePerChange * i, images[i]));
	}
	//�Ō�ɍŏ���gh�Ɠ����̂�����
	frameAndImages.insert(std::make_pair(framePerChange * length, images[0]));
}


