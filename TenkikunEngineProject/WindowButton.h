#pragma once

#include "TriggerRect.h"
#include <functional>
#include "Image.h"

using namespace std;

class Image;
class WindowButton : public TriggerRect
{
	public:
		WindowButton(float startX, float startY, float width, float height, Image* image);

		void Draw();

		void SetImage(Image* image);
		Image* GetImage();

		virtual void PreparationLibrate() override;

	private:
		Image* image = nullptr;	//‰æ‘œ
};

