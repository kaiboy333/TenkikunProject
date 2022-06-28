#include "ProjectFileManager.h"
#include "DxLib.h"

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

std::filesystem::path ProjectFileManager::currentPath;

std::filesystem::path ProjectFileManager::assetFilePath;

std::string ProjectFileManager::assetParentPathName = "";

std::vector<std::filesystem::path> ProjectFileManager::dragFilePathes;
