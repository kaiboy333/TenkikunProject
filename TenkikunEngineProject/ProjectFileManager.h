#pragma once

#include <filesystem>

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
			None,
		};

		static std::filesystem::path currentPath;	//現在のパス

		static std::filesystem::path assetFilePath;	//アセットフォルダがあるパス

		//アセットの絶対パスのファイル名だけ除いたもの
		static std::string assetParentPathName;

		//ドラッグされたファイルのパスたち
		static std::vector<std::filesystem::path> dragFilePathes;

		ProjectFileManager();

		static void Update();

		static FileType GetFileType(std::filesystem::path path);	//指定のファイルはそのタイプであるか

		static void CreateKumoFile(std::filesystem::path path);	//ファイル専用のくも(メタ)ファイルを作成する
};

