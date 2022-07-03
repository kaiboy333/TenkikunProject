#include "ImageIcon.h"

ImageIcon::ImageIcon(float startX, float startY, float width, float height, Window* parentWindow, std::string imageFileName, std::filesystem::path path) : FileIcon(startX, startY, width, height, parentWindow, imageFileName, path)
{
}

void ImageIcon::Draw()
{
	if (iconGH) {
		//�A�C�R�����̎l�p��`��(�A�C�R���w�i)
		DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(200, 200, 200), TRUE);
	}

	FileIcon::Draw();
}
