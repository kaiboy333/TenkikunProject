#pragma once

#include "DxLib.h"
#include <vector>
#include "TriggerRect.h"

class TriggerRect;
class Window : public Rect
{
	public:
		Window(float startX, float startY, float width, float height);

		virtual void Update();

		virtual void Draw();	//•`‰æ

	private:
};
