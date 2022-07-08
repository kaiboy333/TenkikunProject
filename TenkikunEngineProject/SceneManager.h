#pragma once

#include <iostream>
#include <vector>
#include "Scene.h"
#include <filesystem>
#include <fstream>

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

		SceneManager();

		static void LoadScene(std::filesystem::path scenePath);	//シーンファイルからシーンを作成し、読み込む

		static Scene* GetNowScene();	//現在のシーン(getter)

		//static Scene* AddScene();	//シーンを作成、登録

		static Scene* MakeScene();	//シーンを作成

		static Scene* MakeSceneFromFile(std::filesystem::path scenePath);	//シーンファイルからシーンを作成

	private:
		static Scene* nowScene;	//現在のScene
};

