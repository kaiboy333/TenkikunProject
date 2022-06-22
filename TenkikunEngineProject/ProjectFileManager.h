#pragma once
#include "TriggerRect.h"
#include <filesystem>

class ProjectFileManager :  public TriggerRect
{
	public:
		ProjectFileManager(float startX, float startY, float width, float height, Window* parentWindow);

		std::filesystem::path currentPath = std::filesystem::current_path();	//���݌��Ă���p�X

		void Draw();
};

