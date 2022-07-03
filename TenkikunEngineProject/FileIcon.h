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

		float overWidth = 15;	//アイコンからはみ出すTextBoxの+α幅

		FileIcon(float startX, float startY, float width, float height, Window* parentWindow, std::string imageFileName, std::filesystem::path path);

		virtual void Draw();	//アイコン描画
};

