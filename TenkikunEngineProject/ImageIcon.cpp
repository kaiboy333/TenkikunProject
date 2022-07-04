#include "ImageIcon.h"

ImageIcon::ImageIcon(float startX, float startY, float width, float height, Window* parentWindow, std::string imageFileName, std::filesystem::path path) : FileIcon(startX, startY, width, height, parentWindow, imageFileName, path)
{
}

void ImageIcon::Draw()
{
	if (iconGH) {
		//�摜�̃A���t�@�l�ݒ�
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		//�A�C�R�����̎l�p��`��(�A�C�R���w�i)
		DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(169, 169, 169), TRUE);
	}

	FileIcon::Draw();
}
