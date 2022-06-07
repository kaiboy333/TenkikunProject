#pragma once

#include "Window.h"
#include "TreeList.h"

class HierarchyWindow :  public Window
{
	public:
		HierarchyWindow();

		virtual void Update() override;
		virtual void Draw() override;
};

