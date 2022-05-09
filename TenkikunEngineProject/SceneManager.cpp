#include "SceneManager.h"

SceneManager::SceneManager()
{
	AddScene();	//シーンを作成
}

void SceneManager::LoadScene(std::string targetSceneName)
{
	for (Scene* scene : scenes) {
		//同じ名前だったら
		if (scene->sceneName == targetSceneName) {
			//それを現在のシーンに設定
			nowScene = scene;
			return;
		}
	}
	std::cout << "Sceneが見つかりません" << std::endl;
}

void SceneManager::LoadScene(Scene* targetScene)
{
	for (Scene* scene : scenes) {
		//同じだったら
		if (scene == targetScene) {
			//それを現在のシーンに設定
			nowScene = scene;
			return;
		}
	}
	std::cout << "Sceneが見つかりません" << std::endl;
}

Scene* SceneManager::GetNowScene()
{
	return nowScene;
}

Scene* SceneManager::AddScene()
{
	Scene* scene = new Scene();
	scenes.emplace_back(scene);	//リストに追加
	//もし、現在のシーンが登録されていなかったら
	if (nowScene == nullptr) {
		nowScene = scene;	//登録
	}
	scene->Init();
	return scene;
}

std::vector<Scene*> SceneManager::scenes;	//シーンたち
Scene* SceneManager::nowScene;	//現在のScene
