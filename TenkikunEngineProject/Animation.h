#pragma once

#include <iostream>
#include <map>
#include "Image.h"
#include <vector>
#include "Info.h"

class Image;
class Animation : public Info
{
	public:
		std::map<int, Image*> animationKeys;	//�摜�Ƃ��ꂪ����Frame��

		bool isLoop = true;

		void AddAnimationKey(std::vector<Image*> images, int timeInterVal = 5);

		//Animation(std::vector<Image*> images, int framePerChange);

		Animation(std::filesystem::path path);

		virtual void PreparationLibrate() override;
};

//inline Animation::Animation(std::vector<Image*> images, int framePerChange = 5)
//{
//	int length = static_cast<int>(images.size());
//	for (int i = 0; i < length; i++) {
//		//framePerChange�ÂJ���ē���Ă���
//		frameAndImages.insert(std::make_pair(framePerChange * i, images[i]));
//	}
//	//�Ō�ɍŏ���gh�Ɠ����̂�����
//	frameAndImages.insert(std::make_pair(framePerChange * length, images[0]));
//}


