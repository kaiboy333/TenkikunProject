#include "ImageIcon.h"

ImageIcon::ImageIcon(float startX, float startY, float width, float height, Window* parentWindow, std::string imageFileName, std::filesystem::path path) : FileIcon(startX, startY, width, height, parentWindow, imageFileName, path)
{
}

void ImageIcon::Draw()
{
	if (iconGH) {
		//アイコン後ろの四角を描画(アイコン背景)
		DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(200, 200, 200), TRUE);
	}

	FileIcon::Draw();
}
