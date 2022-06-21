#pragma once

#include "Window.h"
#include "TreeList.h"

class TreeList;
class ProjectWindow : public Window
{
	public:
		TreeList* treeList = nullptr;

		ProjectWindow();

		virtual void Update() override;

		virtual void Draw() override;
};

