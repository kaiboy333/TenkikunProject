#pragma once
#include "TriggerRect.h"
#include <filesystem>

class FilePrintRect :  public TriggerRect
{
	public:
		FilePrintRect(float startX, float startY, float width, float height, Window* parentWindow);

		void Draw();
};

