#pragma once

#include "DxLib.h"
#include "TriggerRect.h"
#include <vector>

class TriggerRect;
class Window : public TriggerRect
{
	public:
		Window(float startX, float startY, float width, float height);

		virtual void Draw();	//•`‰æ
};

