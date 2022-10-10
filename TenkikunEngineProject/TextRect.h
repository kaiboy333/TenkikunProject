#pragma once

#include "Rect.h"
#include <iostream>

class TextRect : public Rect
{
	public:
		TextRect(float startX, float startY, std::string text);

		void SetText(std::string text);
		std::string GetText();

		virtual void Draw();

		virtual void PreparationLibrate() override;

	private:
		std::string text;	//テキスト
};

