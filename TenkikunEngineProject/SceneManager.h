#pragma once

#include <iostream>
#include <vector>
#include "Scene.h"
#include <filesystem>
#include <fstream>
#include <map>

class Scene;
class SceneManager
{
	public:
		enum class PlayMode
		{
			EDIT,	//エンジンの編集時
			PLAY,	//Playモード
			STOP	//Playモードでの一時停止
		};

		static PlayMode playMode;

		static std::map<std::string, std::filesystem::path> scenePathes;	//シーン名とそのパス

		SceneManager();

		static void LoadScene(std::string sceneName);	//シーンの名前からシーンを作成し、読み込む

		static Scene* GetNowScene();	//現在のシーン(getter)

		static void SetNowScene(Scene* scene);	//現在のシーンをセット

		static void MakeScene(std::filesystem::path parentPath);	//シーンを作成

		static void SaveScene();	//現在のシーンをセーブ

	private:
		static Scene* nowScene;	//現在のScene
};

