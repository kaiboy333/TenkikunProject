#include "ScrollRect.h"

ScrollRect::ScrollRect(float startX, float startY, float width, float height, float scrollWidth, float scrollHeight, Window* parentWindow) : TriggerRect(startX, startY, width, height, parentWindow)
{
	this->startScrollX = startX;
	this->startScrollY = startY;
	this->scrollWidth = scrollWidth;
	this->scrollHeight = scrollHeight;
}
