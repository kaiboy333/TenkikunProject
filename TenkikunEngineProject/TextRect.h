#pragma once

#include "Rect.h"
#include <iostream>

using namespace std;

class TextRect : public Rect
{
	public:
		TextRect(float startX, float startY, string text);

		void SetText(string text);
		string GetText();

		virtual void Draw();

	private:
		string text;	//テキスト
};

