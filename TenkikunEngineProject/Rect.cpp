#include "Rect.h"

Rect::Rect(float startX, float startY, float width, float height)
{
	this->startX = startX;
	this->startY = startY;
	this->width = width;
	this->height = height;
}

void Rect::Draw()
{
}

bool Rect::IsPointIn(float x, float y)
{
	return startX <= x && startX + width >= x && startY <= y && startY + height >= y;
}
