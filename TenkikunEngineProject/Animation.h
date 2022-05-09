#pragma once

#include <iostream>
#include <map>
#include "Image.h"
#include <vector>

class Animation
{
	public:
		std::map<int, Image*> frameAndImages;	//‰æ‘œ‚Æ‚»‚ê‚ª—ˆ‚éFrame”

		bool isLoop = true;

		Animation(std::vector<Image*> images, int framePerChange);
};

inline Animation::Animation(std::vector<Image*> images, int framePerChange = 5)
{
	int length = static_cast<int>(images.size());
	for (int i = 0; i < length; i++) {
		//framePerChange‚Ã‚ÂŠJ‚¯‚Ä“ü‚ê‚Ä‚¢‚­
		frameAndImages.insert(std::make_pair(framePerChange * i, images[i]));
	}
	//ÅŒã‚ÉÅ‰‚Ìgh‚Æ“¯‚¶‚Ì‚ğ“ü‚ê‚é
	frameAndImages.insert(std::make_pair(framePerChange * length, images[0]));
}


