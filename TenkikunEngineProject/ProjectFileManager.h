#pragma once

#include <filesystem>
#include <unordered_map>
#include "Info.h"

class ProjectFileManager
{
	public:
		//ファイルの種類
		enum class FileType {
			Image,
			Folder,
			Script_cpp,
			Script_hpp,
			Script_h,
			Kumo,
			None,
		};

		static std::filesystem::path currentPath;	//現在のパス

		static std::filesystem::path assetFilePath;	//アセットフォルダがあるパス

		//アセットの絶対パスのファイル名だけ除いたもの
		static std::string assetParentPathName;

		//ドラッグされたファイルのパスたち
		static std::vector<std::filesystem::path> dragFilePathes;

		//Infoが入ったもの
		static std::unordered_map<std::string, Info*> idInfos;

		ProjectFileManager();

		static void Update();

		static FileType GetFileType(std::filesystem::path path);	//指定のファイルはそのタイプであるか

		static void CreateAndLoadKumoFile(std::filesystem::path kumoPath);	//ファイル専用のくも(メタ)ファイルをチェック

	private:
		static void WriteToKumoFile(std::filesystem::path kumoPath);	//雲ファイルに記述する
		static void WriteToInfo(std::filesystem::path kumoPath);	//雲ファイルからInfoを作成

		static std::string CreateGUID();	//GUIDを生成する(stringで)
};

