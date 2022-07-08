#include "SceneManager.h"
#include "ProjectFileManager.h"
#include "MyString.h"

SceneManager::SceneManager()
{
	MakeScene();	//シーンを作成
}

void SceneManager::LoadScene(std::filesystem::path scenePath)
{
	//シーンファイルだったら
	if (ProjectFileManager::GetFileType(scenePath) == ProjectFileManager::FileType::Scene) {
		//シーンファイルを開く
		std::ifstream ifs(scenePath);
		//開けたら
		if (ifs) {
			//シーンファイルから読み込み、シーンを作成
			Scene* scene = MakeSceneFromFile(scenePath);
			//シーンのパスを設定
			scene->scenePath = scenePath;
			nowScene = scene;	//登録
			scene->Init();	//初期化
		}
	}
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
	Scene* scene = nullptr;

	//今のパスにシーンファイルを設定
	std::filesystem::path scenePath(ProjectFileManager::currentPath.string() + ".scene");

	std::ofstream ofs(scenePath.c_str());
	//シーンファイルを作成、開く
	if (ofs) {
		//シーンを作成
		scene = new Scene();
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

	return scene;
}

Scene* SceneManager::MakeSceneFromFile(std::filesystem::path scenePath)
{
	//行たちを読み込み
	std::vector<std::string> lines = MyString::GetLines(scenePath);
}

Scene* SceneManager::nowScene = nullptr;	//現在のScene
SceneManager::PlayMode SceneManager::playMode = PlayMode::EDIT;	//初期は編集モード
