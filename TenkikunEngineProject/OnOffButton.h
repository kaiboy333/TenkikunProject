#pragma once

#include "WindowButton.h"

class OnOffButton : public WindowButton
{
	public:
		OnOffButton(float startX, float startY, float width, float height, Image* image, std::vector<function<void()>> buttonFunc);

		bool isDown = false;	//ƒ{ƒ^ƒ“‚ª‚Ö‚±‚ñ‚Å‚¢‚éó‘Ô‚©

		Image* image;	//‰æ‘œ

		virtual void PreparationLibrate() override;

		virtual void Draw() override;

	protected:
		std::vector<function<void()>> buttonFunc;

		unsigned int downColor = GetColor(100, 100, 100);
};

