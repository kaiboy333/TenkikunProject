#pragma once

#include <iostream>
#include <map>
#include "Image.h"
#include <vector>

class Animation : public SceneInfo
{
	public:
		std::map<int, Image*> frameAndImages;	//画像とそれが来るFrame数

		bool isLoop = true;

		Animation(std::vector<Image*> images, int framePerChange);
};

inline Animation::Animation(std::vector<Image*> images, int framePerChange = 5)
{
	int length = static_cast<int>(images.size());
	for (int i = 0; i < length; i++) {
		//framePerChangeづつ開けて入れていく
		frameAndImages.insert(std::make_pair(framePerChange * i, images[i]));
	}
	//最後に最初のghと同じのを入れる
	frameAndImages.insert(std::make_pair(framePerChange * length, images[0]));
}


