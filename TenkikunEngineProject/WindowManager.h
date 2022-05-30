#pragma once

#include "Window.h"
#include "GameWindow.h"
#include "HierarchyWindow.h"

class GameWindow;
class HierarchyWindow;
class WindowManager
{
	public:
		static GameWindow* gameWindow;
		static HierarchyWindow* hierarchyWindow;
		static void Draw();
};

