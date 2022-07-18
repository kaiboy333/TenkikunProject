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
	//あるなら
	else {
		//マップの最初のシーンパスを読み込む
		LoadScene(scenePathes.begin()->first);
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
		Debug::Log("そのSceneの名前は存在しません。");
	}
}

Scene* SceneManager::GetNowScene()
{
	return nowScene;
}

void SceneManager::MakeScene()
{
	//シーンを作成
	Scene* scene = new Scene();

	//もし、現在のシーンが登録されていなかったら
	if (nowScene == nullptr) {
		nowScene = scene;	//登録
	}
	scene->Init();	//初期化

	//今のパスの中ににシーンファイルを設定
	std::filesystem::path scenePath(ProjectFileManager::currentPath.string() + "\\" + scene->GetName() + ".scene");
	//シーンのパスを設定
	scene->scenePath = scenePath;

	//シーンリストに追加
	scenePathes.insert(std::make_pair(scene->GetName(), scenePath));

	std::ofstream ofs(scenePath.c_str());
	//シーンファイルを作成、開く
	if (ofs) {
		//ツリーリストに追加、雲ファイルも作成
		WindowManager::projectWindow->SetFileChildrenToTreeList(scenePath);
		//ファイルアイコン更新
		WindowManager::projectWindow->filePrintRect->LoadFoler();

		scene->CreateCamera();	//カメラ生成
		scene->CreateTenkikun();	//天気くん生成


		//シーンをセーブ
		SaveScene();
	}
}

void SceneManager::SaveScene()
{
	//編集モードなら
	if (playMode == PlayMode::EDIT) {
		//現在のシーンをセーブ(シーンファイルに書き込む)
		ProjectFileManager::WriteToSceneFile(nowScene);
		Debug::Log(nowScene->GetName() + "をセーブしました。");
	}
	else {
		Debug::Log("プレイ中はセーブできません。");
	}
}

Scene* SceneManager::nowScene = nullptr;	//現在のScene
SceneManager::PlayMode SceneManager::playMode = PlayMode::EDIT;	//初期は編集モード

std::unordered_map<std::string, std::filesystem::path> SceneManager::scenePathes;
