#pragma once

#include "TriggerRect.h"
#include "Image.h"

class MenuList;
class MenuNode : public TriggerRect
{
	public:
		std::string element;

		Image* arrawImage = nullptr;
		float arrawWidth;

		static MenuNode* selectedMenuNode;

		MenuNode(float startX, float startY, std::string element, MenuList* parentMenuList);

		void Draw();

		void SetChildMenuList(MenuList* childMenuList);
		MenuList* GetChildMenuList();

		MenuList* GetParentMenuList();

		virtual void PreparationLibrate() override;

	private:
		MenuList* childMenuList = nullptr;

		MenuList* parentMenuList = nullptr;
};

