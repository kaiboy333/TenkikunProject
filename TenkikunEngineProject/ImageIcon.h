#pragma once

#include "FileIcon.h"

class ImageIcon : public FileIcon
{
	public:
		ImageIcon(float startX, float startY, float iconWidth, float iconHeight, float blankWidth, float blankHeight, Window* parentWindow, std::string imageFileName, std::filesystem::path path);
};

