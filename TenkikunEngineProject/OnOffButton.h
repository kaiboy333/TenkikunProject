#pragma once

#include "WindowButton.h"

class OnOffButton : public WindowButton
{
	public:
		OnOffButton(float startX, float startY, float width, float height, Image* image, std::vector<function<void()>> buttonFunc, unsigned int downColor = GetColor(30, 144, 255));

		virtual void PreparationLibrate() override;

		bool isDown = false;	//ボタンがへこんでいる状態か

		virtual void Draw() override;

	private:
		std::vector<function<void()>> buttonFunc;

		unsigned int downColor;
};

