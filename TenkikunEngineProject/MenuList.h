#pragma once

#include "Rect.h"
#include "MenuNode.h"

class MenuList : public Rect
{
	public:
		static const int WIDTH = 100;

		MenuList(float startX, float startY, std::vector<std::string> elements);
};

