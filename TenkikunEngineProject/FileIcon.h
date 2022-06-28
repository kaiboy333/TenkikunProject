#pragma once

#include "TriggerRect.h"
#include <filesystem>

class FileIcon : public TriggerRect
{
	public:
		int iconGH = 0;

		std::filesystem::path path;	//対になるファイルのパス

		FileIcon(float startX, float startY, float width, float height, Window* parentWindow, std::string imageFileName, std::filesystem::path path);

		void IconDraw();	//アイコン描画
};

