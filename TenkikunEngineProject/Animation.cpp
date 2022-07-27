#include "Animation.h"

Animation::Animation(std::filesystem::path path) : Info(path)
{

}

void Animation::AddAnimationKey(std::vector<Image*> images, int timeInterVal)
{
	int length = static_cast<int>(images.size());
	for (int i = 0; i < length; i++) {
		//framePerChange‚Ã‚ÂŠJ‚¯‚Ä“ü‚ê‚Ä‚¢‚­
		animationKeys.insert(std::make_pair(timeInterVal * i, images[i]));
	}
	//ÅŒã‚ÉÅ‰‚Ìgh‚Æ“¯‚¶‚Ì‚ð“ü‚ê‚é
	animationKeys.insert(std::make_pair(timeInterVal * length, images[0]));
}