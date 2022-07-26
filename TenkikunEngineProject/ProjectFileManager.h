#pragma once

#include <filesystem>
#include <unordered_map>
#include "Info.h"
#include <random>
#include "Scene.h"
#include "AnimatorController.h"

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
			Animation,
			AnimatorController,
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

		//static std::unordered_map<Info*, int> infoAndFileID;

		static std::unordered_map<std::string, Info*> guidAndInfo;

		//sceneInfos
		static std::unordered_map<int, SceneInfo*> sceneInfos;

		static std::unordered_map<std::string, std::filesystem::path> guidAndPath;

		ProjectFileManager();

		static void Update();

		static FileType GetFileType(std::filesystem::path path);	//指定のファイルはそのタイプであるか

		static void CreateAndLoadKumoFile(std::filesystem::path kumoPath);	//ファイル専用のくも(メタ)ファイルをチェック

		static Info* CreateInfo(std::filesystem::path path);	//ファイルからInfoを作成

		static void WriteToKumoFile(std::filesystem::path kumoPath, Info* info);	//雲ファイルに記述する

		static void WriteToFile();	//保存するファイルに情報を記述する
		static void LoadFromFile();	//すべての保存ファイルから情報を読み込む

		static void WriteToSceneFile(Scene* scene);	//現在のシーンの情報をシーンファイルに書き込む
		static void LoadFromSceneFile(std::filesystem::path scenePath);	//シーンファイルからシーンを作成

		//template<class T>
		//static std::vector<T*> GetSpecificGUIDInfos();	//guidInfosにある特定(T)のクラスを取得する

		static int CreateFileID();	//fileIDを生成する(intで)
		static std::string CreateGUID();	//GUIDを生成する(stringで)

		static std::string GetNameWithoutExtensionName(std::filesystem::path path);	//拡張子を抜いたファイル名取得

	private:
		static void WriteToAnimationFile(Animation* animation);	//アニメーションファイルに記述する
		static void LoadFromAnimationFile(std::filesystem::path animationPath);	//アニメーションファイルからアニメーションを作成

		static void WriteToAnimatorControllerFile(AnimatorController* ac);	//現在のacの情報をacファイルに書き込む
		static void LoadFromAnimatorControllerFile(std::filesystem::path acPath);	//acファイルからacを作成

		template<class T, class K>
		static K GetValue(std::unordered_map<T, K>& map, T key, K value);	//マップのvalueを取得、なかったら新しいvalueを追加、取得

		static std::string GetGUIDFromKumoPath(std::filesystem::path kumoPath);	//kumoPathからguidを取得
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

//template<class T>
//inline std::vector<T*> ProjectFileManager::GetSpecificGUIDInfos()
//{
//	std::vector<T*> infos;
//
//	//回す
//	for (std::pair pair : idInfos) {
//		//このInfoクラスがTクラスであるなら
//		//キャスト変換可能なら
//		if (static_cast<T*>(pair.second) != nullptr) {
//			//キャストしてInfoを取得
//			T* info = static_cast<T*>(pair.second);
//			//リストに追加
//			infos.push_back(info);
//		}
//	}
//
//	return infos;
//}
