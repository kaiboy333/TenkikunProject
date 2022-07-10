#include "SceneManager.h"
#include "ProjectFileManager.h"
#include "MyString.h"
#include "Debug.h"

SceneManager::SceneManager()
{
	//シーンが何もないなら
	if (scenePathes.size() == 0) {
		MakeScene();	//シーンを作成
	}
}

void SceneManager::LoadScene(std::string sceneName)
{
	//シーンが存在するなら
	if (scenePathes.contains(sceneName)) {
		//シーンパスを取得
		std::filesystem::path scenePath = scenePathes[sceneName];
		//シーンファイルだったら
		if (ProjectFileManager::GetFileType(scenePath) == ProjectFileManager::FileType::Scene) {
			//シーンファイルを開く
			std::ifstream ifs(scenePath);
			//開けたら
			if (ifs) {
				//シーンを作成
				Scene* scene = new Scene();
				//シーンのパスを設定
				scene->scenePath = scenePath;
				nowScene = scene;	//登録
				scene->Init();	//初期化
				//シーンファイルから読み込む
				ProjectFileManager::LoadSceneFromFile(scenePath, scene);
			}
		}
	}
	else {
		Debug::Log("そのSceneの名前は存在しません。\n");
	}
}

Scene* SceneManager::GetNowScene()
{
	return nowScene;
}

void SceneManager::MakeScene()
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

		scene->CreateCamera();	//カメラ生成
		scene->CreateSquare();	//四角生成


		//ツリーリストに追加、雲ファイルも作成
		WindowManager::projectWindow->SetFileChildrenToTreeList(scenePath);
		//ファイルアイコン更新
		WindowManager::projectWindow->filePrintRect->LoadFoler();
	}
}

Scene* SceneManager::nowScene = nullptr;	//現在のScene
SceneManager::PlayMode SceneManager::playMode = PlayMode::EDIT;	//初期は編集モード

std::unordered_map<std::string, std::filesystem::path> SceneManager::scenePathes;
