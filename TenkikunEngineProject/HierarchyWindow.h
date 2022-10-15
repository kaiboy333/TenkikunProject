#pragma once

#include "Window.h"
#include "TreeList.h"

class TreeList;
class HierarchyWindow :  public Window
{
	public:
		TreeList* treeList = nullptr;

		HierarchyWindow();

		virtual void Update() override;
		virtual void Draw() override;
};

