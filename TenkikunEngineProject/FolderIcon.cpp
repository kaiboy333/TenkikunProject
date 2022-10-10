#include "FolderIcon.h"
#include "WindowManager.h"
#include "ProjectFileManager.h"

FolderIcon::FolderIcon(float startX, float startY, float iconWidth, float iconHeight, float blankWidth, float blankHeight, std::string imageFileName, std::filesystem::path path) : FileIcon(startX, startY, iconWidth, iconHeight, blankWidth, blankHeight, imageFileName, path)
{
	//イベントを追加(ダブルクリックをしたら)
	this->mouseDoubleClickEvents.push_back(std::make_pair(GetEventNo(), [this]() {
		//現在のパスにさっきのパスを入れる
		ProjectFileManager::currentPath = this->path;
		//パス内のフォルダ更新
		WindowManager::projectWindow->filePrintRect->LoadFoler();
	}));
}

