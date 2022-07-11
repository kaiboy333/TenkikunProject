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
		static std::filesystem::path resourceFilePath;	//リソースフォルダがあるパス
		static std::filesystem::path imageFilePath;	//エンジンで使う画像が入っているフォルダのパス

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

		static void LoadSceneFromFile(std::filesystem::path scenePath, Scene* scene);	//シーンファイルからシーンを作成

		template<class T>
		static std::vector<T*> GetSpecificInfos();	//idInfosにある特定(T)のクラスを取得する

	private:
		static void WriteToInfo(std::filesystem::path kumoPath);	//雲ファイルからInfoを作成

		static std::string CreateGUID();	//GUIDを生成する(stringで)

		static int CreateFileID();	//fileIDを生成する(intで)

		template<class T, class K>
		static K GetValue(std::unordered_map<T, K>& map, T key, K value);	//マップのvalueを取得、なかったら新しいvalueを取得
};

template<class T, class K>
inline K ProjectFileManager::GetValue(std::unordered_map<T, K>& map, T key, K value)
{
	//キーが見つからなかったなら
	if (!map.contains(key)) {
		//新しく作る
		map.insert(std::make_pair(key, value));
		//その値を返す
		return value;
	}
	else {
		//既にある値を返す
		return map[key];
	}
}

template<class T>
inline std::vector<T*> ProjectFileManager::GetSpecificInfos()
{
	std::vector<T*> infos;

	//回す
	for (std::pair pair : idInfos) {
		//このInfoクラスがTクラスであるなら
		//キャスト変換可能なら
		if (static_cast<T*>(pair.second) != nullptr) {
			//キャストしてInfoを取得
			T* info = static_cast<T*>(pair.second);
			//リストに追加
			infos.push_back(info);
		}
	}

	return infos;
}
