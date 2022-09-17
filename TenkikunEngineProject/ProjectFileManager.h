#pragma once

#include <filesystem>
#include <map>
#include <random>
#include "Scene.h"
#include "Animation.h"
#include "AnimatorController.h"
#include <string>

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
		static const int ID_MIN = 1;
		static const int ID_MAX = 100000000;

		static std::filesystem::path currentPath;	//現在のパス

		static std::filesystem::path assetFilePath;	//アセットフォルダがあるパス(デフォルト)
		static std::filesystem::path resourceFilePath;	//リソースフォルダがあるパス(デフォルト)
		static std::filesystem::path imageFilePath;	//エンジンで使う画像が入っているフォルダのパス(今は機能しない)
		static std::filesystem::path sceneFilePath;	//シーンを入れるためのフォルダのパス(デフォルト)

		//アセットの絶対パスのファイル名だけ除いたもの
		static std::string assetParentPathName;

		//ドラッグされたファイルのパスたち
		static std::vector<std::filesystem::path> dragFilePathes;

		//static std::unordered_map<Info*, int> infoAndFileID;

		//static std::unordered_map<std::string, Info*> guidAndInfo;

		//static std::unordered_map<std::filesystem::path, Info*> pathAndInfo;
		static std::map<std::filesystem::path, Info*> pathAndInfo;

		//sceneInfos
		static std::map<int, SceneInfo*> sceneInfos;

		static std::map<std::string, std::filesystem::path> guidAndPath;

		ProjectFileManager();

		static void Update();

		static FileType GetFileType(std::filesystem::path path);	//指定のファイルはそのタイプであるか
		static bool IsFileType(std::filesystem::path path);	//ファイルタイプを認識できるか

		static std::string WriteToKumoFile(std::filesystem::path kumoPath);	//雲ファイルに記述する
		static void LoadFromKumoFile(std::filesystem::path kumoPath);	//雲ファイルから読み込み、Infoを作成

		//static Info* CreateInfo(std::filesystem::path path);	//ファイルからInfoを作成

		static void WriteToFile();	//保存するファイルに情報を記述する
		static void LoadFromFile();	//すべての保存ファイルから情報を読み込む

		static void WriteToSceneFile(Scene* scene);	//現在のシーンの情報をシーンファイルに書き込む
		static void LoadFromSceneFile(std::filesystem::path scenePath);	//シーンファイルからシーンを作成

		static int CreateFileID();	//fileIDを生成する(intで)
		static std::string CreateGUID();	//GUIDを生成する(stringで)

		static std::string GetNameWithoutExtensionName(std::filesystem::path path);	//拡張子を抜いたファイル名取得

		static void CheckAddFile(std::filesystem::path path);	//追加されたファイルを子も含めチェック

	private:
		static std::string GetGUIDFromKumoFile(std::filesystem::path kumoPath);	//雲ファイルからguidを取得

		static void WriteToAnimationFile(Animation* animation);	//アニメーションファイルに記述する
		static void LoadFromAnimationFile(std::filesystem::path animationPath);	//アニメーションファイルからアニメーションを作成

		static void WriteToAnimatorControllerFile(AnimatorController* ac);	//現在のacの情報をacファイルに書き込む
		static void LoadFromAnimatorControllerFile(std::filesystem::path acPath);	//acファイルからacを作成

		template<class T, class K>
		static K GetValue(std::map<T, K>& map, T key, K value);	//マップのvalueを取得、なかったら新しいvalueを追加、取得

		static void CreateAndLoadKumoFile(std::filesystem::path path);	//ファイルから雲ファイルを作成したり読み込んだりする
};

template<class T, class K>
inline K ProjectFileManager::GetValue(std::map<T, K>& map, T key, K value)
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
