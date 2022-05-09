#pragma once

class Window
{
	public:
		int width, height;
		float startX = 0, startY = 0;

		Window(int width, int height, float startX, float startY);

		virtual void Draw() = 0;	//•`‰æ
};

