#pragma once

#include "TriggerRect.h"
#include "Image.h"

class MenuList;
class MenuNode : public TriggerRect
{
	public:
		std::string element;

		MenuList* menuList = nullptr;

		Image* arrawImage = nullptr;
		float arrawWidth;

		MenuNode(float startX, float startY, std::string element);

		void Draw();
};

