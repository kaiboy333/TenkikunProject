#pragma once

#include "TriggerRect.h"
#include <filesystem>
#include "TextBox.h"

class FileIcon : public TriggerRect
{
	public:
		int iconGH = 0;

		std::filesystem::path path;	//対になるファイルのパス

		TextBox* fileNameRect = nullptr;	//ファイル名のTextBox

		float iconWidth, iconHeight;	//アイコンの幅、高さ

		static const float overWidth;	//アイコンからはみ出すTextBoxの+α幅

		float blankWidth, blankHeight;	//枠の幅、高さ

		FileIcon(float startX, float startY, float iconWidth, float iconHeight, float blankWidth, float blankHeight, std::string imageFileName, std::filesystem::path path);

		virtual void Draw();	//アイコン描画

		virtual void PreparationLibrate() override;

	protected:
		bool isImageIcon = false;
};

