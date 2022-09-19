#include "SceneManager.h"
#include "ProjectFileManager.h"
#include "MyString.h"
#include "Debug.h"
#include "CreateBallScript.h"

SceneManager::SceneManager()
{
	//シーンが何もないなら
	if (scenePathes.size() == 0) {
		MakeScene(ProjectFileManager::sceneFilePath);	//シーンを作成
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
				ProjectFileManager::LoadFromFile();	//他のファイルを読み込む
				ProjectFileManager::LoadFromSceneFile(scenePath);	//シーンファイルからシーンを再現
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

void SceneManager::MakeScene(std::filesystem::path parentPath)
{
	//親がフォルダーじゃないなら作らない
	if (ProjectFileManager::GetFileType(parentPath) != ProjectFileManager::FileType::Folder)
		return;

	//シーンを作成
	Scene* scene = new Scene();

	//もし、現在のシーンが登録されていなかったら
	if (nowScene == nullptr) {
		nowScene = scene;	//登録
	}
	scene->Init();	//初期化

	//親のフォルダ内の中にシーンファイルを設定
	std::filesystem::path scenePath(parentPath.string() + "\\" + scene->GetName() + ".scene");
	//シーンのパスを設定
	scene->scenePath = scenePath;	//ファイルを作成
	std::ofstream ofs(scenePath.c_str());

	//雲ファイルを作成
	ProjectFileManager::WriteToKumoFile(scenePath.string() + ".kumo");
	WindowManager::projectWindow->filePrintRect->LoadFoler();

	//シーンリストに追加
	scenePathes.insert(std::make_pair(scene->GetName(), scenePath));

	scene->CreateCamera(false);	//カメラ生成
	//scene->CreateTenkikun(false);	//天気くん生成
	//scene->CreateSquare(false);
	//GameObject* circle = scene->CreateCircle(false);
	//circle->transform->position = Vector3(-50, 0, 0);
	//GameObject* circle2 = scene->CreateCircle(false);
	//circle2->transform->position = Vector3(50, 0, 0);
	//scene->CreateUnityChan(false);	//Unityちゃん生成

	GameObject* o = scene->CreateEmpty(false);
	o->AddComponent<CreateBallScript>();

	//シーンをセーブ
	SaveScene();
}

void SceneManager::SetNowScene(Scene* scene)
{
	nowScene = scene;
}

void SceneManager::SaveScene()
{
	//編集モードなら
	if (playMode == PlayMode::EDIT) {
		std::unordered_map<SceneInfo*, int> idInfos;
		//シーン以外の情報をファイルに書き込む
		ProjectFileManager::WriteToFile();
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

std::map<std::string, std::filesystem::path> SceneManager::scenePathes;
