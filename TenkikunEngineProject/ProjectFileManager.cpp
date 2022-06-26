#include "ProjectFileManager.h"

ProjectFileManager::ProjectFileManager()
{
	//アセットのパスを作成
	assetFilePath = std::filesystem::current_path().string() + "\\Asset";
	//アセットの親の絶対パスにバックスラッシュ追加
	assetParentPathName = assetFilePath.parent_path().string() + "\\";
	//アセットフォルダが存在しないなら
	if (!std::filesystem::exists(assetFilePath)) {
		//フォルダを作成
		std::filesystem::create_directory(assetFilePath);
	}
	//初期の現在パスはアセットフォルダにする
	currentPath = assetFilePath;
}

std::filesystem::path ProjectFileManager::currentPath;

std::filesystem::path ProjectFileManager::assetFilePath;

std::string ProjectFileManager::assetParentPathName = "";
