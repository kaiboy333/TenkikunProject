#include "FileIcon.h"
#include "ImageManager.h"
#include "FontManager.h"

FileIcon::FileIcon(float startX, float startY, float width, float height, Window* parentWindow, std::string imageFileName, std::filesystem::path path) : TriggerRect(startX, startY, width, height, parentWindow)
{
	iconGH = ImageManager::LoadAndGetImage(imageFileName);	//�摜���擾
	this->path = path;	//�΂ɂȂ�t�@�C���̃p�X���Z�b�g
	fileNameRect = new TextBox(startX - overWidth / 2, startY + height, width + overWidth, FontManager::systemFont->GetFontHeight(), parentWindow, false, path.filename().string());	//TextBox�쐬
}

void FileIcon::Draw()
{
	if (iconGH) {
		int imageWidth, imageHeight;
		GetGraphSize(iconGH, &imageWidth, &imageHeight);
		//�摜�̃A���t�@�l�ݒ�
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

		//�t�@�C�����̕`��
		fileNameRect->Draw();

		//�摜�̕`��
		DrawRotaGraph3F(startX + width / 2, startY + height / 2, imageWidth / 2.0f, imageHeight / 2.0f, width / imageWidth, height / imageHeight, 0, iconGH, TRUE);
		//�I������Ă�����
		if (GetIsSelected()) {
			//�摜�̃A���t�@�l�ݒ�
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
			//�F��`��
			DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(173, 216, 230), TRUE);
		}
		
		//�摜�̃A���t�@�l�߂�
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
}

const float FileIcon::blankWidth = 10;
const float FileIcon::overWidth = 15;
