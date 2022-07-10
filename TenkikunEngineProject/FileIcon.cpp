#include "FileIcon.h"
#include "ImageManager.h"
#include "FontManager.h"

FileIcon::FileIcon(float startX, float startY, float iconWidth, float iconHeight, float blankWidth, float blankHeight, Window* parentWindow, std::string imageFileName, std::filesystem::path path) : TriggerRect(startX, startY, 2 * blankWidth + iconWidth, 2 * blankHeight + iconHeight + FontManager::systemFont->GetFontHeight(), parentWindow)
{
	iconGH = ImageManager::LoadAndGetImage(imageFileName);	//�摜���擾
	this->iconWidth = iconWidth;
	this->iconHeight = iconHeight;
	this->blankWidth = blankWidth;
	this->blankHeight = blankHeight;
	this->path = path;	//�΂ɂȂ�t�@�C���̃p�X���Z�b�g
	fileNameRect = new TextBox(startX + blankWidth - overWidth / 2, startY + blankHeight + iconHeight, iconWidth + overWidth, FontManager::systemFont->GetFontHeight(), parentWindow, false, path.filename().string());	//TextBox�쐬

	this->mouseClickDownEvents.push_back([this]() {
		//�N���b�N�����Ƃ��Ɏ��g��I�𒆂ɂ���
		this->parentWindow->SetSelectedTriggerRect(this);
	});
}

void FileIcon::Draw()
{
	if (iconGH) {
		int imageWidth, imageHeight;
		GetGraphSize(iconGH, &imageWidth, &imageHeight);

		//�摜�̃A���t�@�l�ݒ�
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

		if (!GetIsSelected() && isOn) {
			//�D�F��`��
			DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(200, 200, 200), TRUE);
		}

		if (isImageIcon) {
			//�A�C�R�����̎l�p��`��(�A�C�R���w�i)
			DrawBoxAA(startX + blankWidth, startY + blankHeight, startX + blankWidth + iconWidth, startY + blankHeight + iconHeight, GetColor(100, 100, 100), TRUE);
		}

		//�t�@�C�����̕`��
		fileNameRect->Draw();

		//�摜�̕`��
		DrawRotaGraph3F(startX + blankWidth + iconWidth / 2, startY + blankHeight + iconHeight / 2, imageWidth / 2.0f, imageHeight / 2.0f, iconWidth / imageWidth, iconHeight / imageHeight, 0, iconGH, TRUE);

		//�I������Ă�����
		if (GetIsSelected()) {
			//�摜�̃A���t�@�l�ݒ�
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
			//�F��`��
			DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(30, 144, 255), TRUE);
		}
		
		//�摜�̃A���t�@�l�߂�
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
}

const float FileIcon::overWidth = 15;