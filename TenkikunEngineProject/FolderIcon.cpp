#include "FolderIcon.h"
#include "WindowManager.h"
#include "ProjectFileManager.h"

FolderIcon::FolderIcon(float startX, float startY, float iconWidth, float iconHeight, float blankWidth, float blankHeight, Window* parentWindow, std::string imageFileName, std::filesystem::path path) : FileIcon(startX, startY, iconWidth, iconHeight, blankWidth, blankHeight, parentWindow, imageFileName, path)
{
	//イベントを追加(ダブルクリックをしたら)
	this->mouseDoubleClickEvents.push_back([this]() {
		//現在のパスにさっきのパスを入れる
		ProjectFileManager::currentPath = this->path;
		//パス内のフォルダ更新
		WindowManager::projectWindow->filePrintRect->LoadFoler();
	});
}

