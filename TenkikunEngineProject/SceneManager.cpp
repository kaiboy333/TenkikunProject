#include "SceneManager.h"
#include "ProjectFileManager.h"

SceneManager::SceneManager()
{
	AddScene();	//シーンを作成
}

void SceneManager::LoadScene(std::filesystem::path scenePath)
{
	//シーンファイルを開く

	//シーンファイルから読み込み、シーンを作成

	//今のシーンに登録
}

Scene* SceneManager::GetNowScene()
{
	return nowScene;
}

//Scene* SceneManager::AddScene()
//{
//	Scene* scene = new Scene();
//	scenes.emplace_back(scene);	//リストに追加
//	//もし、現在のシーンが登録されていなかったら
//	if (nowScene == nullptr) {
//		nowScene = scene;	//登録
//	}
//	scene->Init();
//	return scene;
//}

Scene* SceneManager::MakeScene()
{
	//今のパスにシーンファイルを設定
	std::filesystem::path scenePath(ProjectFileManager::currentPath.string() + ".scene");

	std::ofstream ofs(scenePath.c_str());
	//シーンファイルを作成、開く
	if (ofs) {
		//シーンを作成
		Scene* scene = new Scene();
		//シーンのパスを設定
		scene->scenePath = scenePath;
		//もし、現在のシーンが登録されていなかったら
		if (nowScene == nullptr) {
			nowScene = scene;	//登録
		}
		scene->Init();	//初期化
		//雲ファイルも作成、書き込み
		ProjectFileManager::WriteToKumoFile(std::filesystem::path(scenePath.string() + ".kumo"));
	}

}

Scene* SceneManager::nowScene = nullptr;	//現在のScene
SceneManager::PlayMode SceneManager::playMode = PlayMode::EDIT;	//初期は編集モード
