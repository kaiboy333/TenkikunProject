#pragma once

#include "Window.h"
#include "GameWindow.h"

class WindowManager
{
	public:
		static GameWindow gameWindow;

		static void Draw();
};

