#pragma once

#include "TriggerRect.h"
#include <functional>
#include "Image.h"

using namespace std;

class Image;
class WindowButton : public TriggerRect
{
	public:
		Image* image = nullptr;	//�摜

		WindowButton(float startX, float startY, float width, float height);

		void Draw();

		virtual void PreparationLibrate() override;
};

