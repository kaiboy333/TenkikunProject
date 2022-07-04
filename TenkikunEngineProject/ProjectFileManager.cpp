#include "ProjectFileManager.h"
#include "DxLib.h"
#include <fstream>
#include <iostream>
#include "Debug.h"

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
	currentPath = assetFilePath;	//初期はアセットパス
}

void ProjectFileManager::Update()
{
	//ドラッグファイルリストのリセット
	dragFilePathes.clear();
	//ドラッグされているファイルがあるなら
	if (GetDragFileNum != 0) {
		for (int i = 0; i < GetDragFileNum(); i++) {
			TCHAR currentPath[100] = {};
			//読み込めたら
			if (GetDragFilePath(currentPath) != -1) {
				//ドラッグされたファイルのパスを作成
				std::filesystem::path path = std::filesystem::path(std::string(currentPath));
				//リストに追加
				dragFilePathes.push_back(path);
			}
		}
	}
}

ProjectFileManager::FileType ProjectFileManager::GetFileType(std::filesystem::path path) {
	//パスの拡張子を取得
	std::string extensionName = path.extension().string();

	//初期化
	FileType targetFileType = FileType::None;

	//パスがディレクトリだったら
	if (std::filesystem::is_directory(path)) {
		targetFileType = FileType::Folder;
	}
	else {
		//画像だったら
		if (extensionName == ".png" || extensionName == ".jpg") {
			targetFileType = FileType::Image;
		}
		//スクリプトだったら(cpp)
		else if (extensionName == ".cpp") {
			targetFileType = FileType::Script_cpp;
		}
		//スクリプトだったら(hpp)
		else if (extensionName == ".hpp") {
			targetFileType = FileType::Script_hpp;
		}
		//スクリプトだったら(h)
		else if (extensionName == ".h") {
			targetFileType = FileType::Script_h;
		}
	}

	//タイプを返す
	return targetFileType;
}

void ProjectFileManager::CreateKumoFile(std::filesystem::path path)
{
	//雲ファイルパスを作成
	std::filesystem::path kumoPath = std::filesystem::path(path.string() + ".kumo");

	//ファイルが存在しないなら
	if (!std::filesystem::exists(kumoPath)) {
		//ファイルを作成、開く
		std::ofstream ofs(kumoPath.c_str());
		//開けたら
		if (ofs) {

		}
		else {
			Debug::Log(kumoPath.string() + "は開けませんでした。\n");
		}
	}
}

std::filesystem::path ProjectFileManager::assetFilePath;

std::filesystem::path ProjectFileManager::currentPath;

std::string ProjectFileManager::assetParentPathName = "";

std::vector<std::filesystem::path> ProjectFileManager::dragFilePathes;
