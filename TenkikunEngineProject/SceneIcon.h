#pragma once

#include "FileIcon.h"

class SceneIcon : public FileIcon
{
	public:
		SceneIcon(float startX, float startY, float iconWidth, float iconHeight, float blankWidth, float blankHeight, std::string imageFileName, std::filesystem::path path);
};

