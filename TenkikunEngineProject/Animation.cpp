#include "Animation.h"

Animation::Animation(std::filesystem::path path) : Info(path)
{

}

void Animation::PreparationLibrate()
{
	animationKeys.clear();
}

void Animation::AddAnimationKey(std::vector<Image*> images, int timeInterVal)
{
	int length = static_cast<int>(images.size());
	for (int i = 0; i < length; i++) {
		//framePerChangeづつ開けて入れていく
		animationKeys.insert(std::make_pair(timeInterVal * i, images[i]));
	}
	//最後に最初のghと同じのを入れる
	animationKeys.insert(std::make_pair(timeInterVal * length, images[0]));
}