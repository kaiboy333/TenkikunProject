#pragma once

#include "FileIcon.h"

class ImageIcon : public FileIcon
{
	public:
		ImageIcon(float startX, float startY, float width, float height, Window* parentWindow, std::string imageFileName, std::filesystem::path path);

		virtual void Draw() override;
};

