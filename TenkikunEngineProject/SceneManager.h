#pragma once

#include <iostream>
#include <vector>
#include "Scene.h"

class Scene;
class SceneManager
{
	public:
		SceneManager();

		static void LoadScene(std::string targetSceneName);	//シーンの名前からそのシーンに移動する
		static void LoadScene(Scene* targetScene);	//シーンからそのシーンに移動する

		static Scene* GetNowScene();	//現在のシーン(getter)

		static Scene* AddScene();	//シーンを作成、登録

	private:
		static Scene* nowScene;	//現在のScene
		static std::vector<Scene*> scenes;	//シーンたち
};

