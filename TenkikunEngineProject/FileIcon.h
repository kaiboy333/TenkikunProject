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

		static const float overWidth;	//�A�C�R������͂ݏo��TextBox��+����

		static const float blankWidth;	//�g�̕�

		FileIcon(float startX, float startY, float width, float height, Window* parentWindow, std::string imageFileName, std::filesystem::path path);

		virtual void Draw();	//�A�C�R���`��
};

