#include "ImageIcon.h"

ImageIcon::ImageIcon(float startX, float startY, float iconWidth, float iconHeight, float blankWidth, float blankHeight, Window* parentWindow, std::string imageFileName, std::filesystem::path path) : FileIcon(startX, startY, iconWidth, iconHeight, blankWidth, blankHeight, parentWindow, imageFileName, path)
{
	isImageIcon = true;
}