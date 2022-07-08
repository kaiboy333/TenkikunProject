#pragma once

#include <filesystem>
#include <unordered_map>
#include "Info.h"
#include <random>
#include "Scene.h"

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
			Scene,
			None,
		};

		//ランダム関連(fileID)
		static const int MIN = 1;
		static const int MAX = 100000000;

		static std::random_device rd;
		static std::default_random_engine eng;
		static std::uniform_int_distribution<int> distr;

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

		static void WriteToKumoFile(std::filesystem::path kumoPath);	//雲ファイルに記述する

		static void WriteToSceneFile(Scene* scene);	//現在のシーンの情報をシーンファイルに書き込む

	private:
		static void WriteToInfo(std::filesystem::path kumoPath);	//雲ファイルからInfoを作成

		static std::string CreateGUID();	//GUIDを生成する(stringで)

		static int CreateFileID();	//fileIDを生成する(intで)
};

