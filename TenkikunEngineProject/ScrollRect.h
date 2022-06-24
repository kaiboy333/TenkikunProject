#pragma once
#include "TriggerRect.h"

class ScrollRect : public TriggerRect
{
	public:
		ScrollRect(float startX, float startY, float width, float height, float scrollWidth, float scrollHeight, Window* parentWindow);

		float startScrollX, startScrollY;
		float scrollWidth, scrollHeight;
};

