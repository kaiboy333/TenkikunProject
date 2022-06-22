#pragma once
#include "TriggerRect.h"
#include <filesystem>

class ProjectFileManager :  public TriggerRect
{
	public:
		ProjectFileManager(float startX, float startY, float width, float height, Window* parentWindow);

		std::filesystem::path currentPath = std::filesystem::current_path();	//現在見ているパス

		void Draw();
};

