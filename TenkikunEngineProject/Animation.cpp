#include "Animation.h"

void Animation::AddAnimationKey(std::vector<Image*> images, int timeInterVal)
{
		int length = static_cast<int>(images.size());
		for (int i = 0; i < length; i++) {
			//framePerChange�ÂJ���ē���Ă���
			animationKeys.insert(std::make_pair(timeInterVal * i, images[i]));
		}
		//�Ō�ɍŏ���gh�Ɠ����̂�����
		animationKeys.insert(std::make_pair(timeInterVal * length, images[0]));
}
