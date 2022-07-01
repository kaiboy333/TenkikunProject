#include "FileIcon.h"
#include "ImageManager.h"
#include "FontManager.h"

FileIcon::FileIcon(float startX, float startY, float width, float height, Window* parentWindow, std::string imageFileName, std::filesystem::path path) : TriggerRect(startX, startY, width, height, parentWindow)
{
	iconGH = ImageManager::LoadAndGetImage(imageFileName);	//�摜���擾
	this->path = path;	//�΂ɂȂ�t�@�C���̃p�X���Z�b�g
	fileNameRect = new TextBox(startX, startY + height, width, FontManager::systemFont->GetFontHeight(), parentWindow, path.filename().string());	//TextBox�쐬
}

void FileIcon::IconDraw()
{
	if (iconGH) {
		//�A�C�R�����̎l�p��`��(�A�C�R���w�i)
		DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(200, 200, 200), TRUE);

		int imageWidth, imageHeight;
		GetGraphSize(iconGH, &imageWidth, &imageHeight);
		//�摜�̕`��
		DrawRotaGraph3F(startX + width / 2, startY + height / 2, imageWidth / 2.0f, imageHeight / 2.0f, width / imageWidth, height / imageHeight, 0, iconGH, TRUE);
		//�t�@�C�����̕`��
		fileNameRect->Draw();
	}
}
