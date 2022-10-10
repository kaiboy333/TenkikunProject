#pragma once

#include "TriggerRect.h"
#include <filesystem>
#include "TextBox.h"

class FileIcon : public TriggerRect
{
	public:
		int iconGH = 0;

		std::filesystem::path path;	//�΂ɂȂ�t�@�C���̃p�X

		TextBox* fileNameRect = nullptr;	//�t�@�C������TextBox

		float iconWidth, iconHeight;	//�A�C�R���̕��A����

		static const float overWidth;	//�A�C�R������͂ݏo��TextBox��+����

		float blankWidth, blankHeight;	//�g�̕��A����

		FileIcon(float startX, float startY, float iconWidth, float iconHeight, float blankWidth, float blankHeight, std::string imageFileName, std::filesystem::path path);

		virtual void Draw();	//�A�C�R���`��

		virtual void PreparationLibrate() override;

	protected:
		bool isImageIcon = false;
};

