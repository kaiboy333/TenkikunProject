#pragma once

#include "Rect.h"
#include "MenuNode.h"

class MenuList : public Rect
{
	public:
		static const int WIDTH = 150;

		std::vector<MenuNode*> menuNodes;

		MenuList(float startX, float startY, std::vector<std::string> elements);

		void SetIsVisible(bool isVisible);

		void Draw();

		MenuNode* FindNode(std::string element);	//このメニューリストの中から探す

		virtual void PreparationLibrate() override;

	private:
		bool isVisible = true;
};

