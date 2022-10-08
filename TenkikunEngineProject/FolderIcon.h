#pragma once
#include "FileIcon.h"
class FolderIcon : public FileIcon
{
	public:
		FolderIcon(float startX, float startY, float iconWidth, float iconHeight, float blankWidth, float blankHeight, std::string imageFileName, std::filesystem::path path);
};

