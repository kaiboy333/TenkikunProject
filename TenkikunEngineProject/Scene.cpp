#include "Scene.h"
#include "SceneManager.h"
#include "ImageRenderer.h"
#include "Animator.h"

void Scene::Init()
{
	CreateCamera();	//カメラ生成

	CreateSquare();	//四角い画像を生成
}

void Scene::Update()
{
	for (GameObject* gameObject : gameobjects) {
		gameObject->Update();	//ゲームオブジェクトの更新
	}
}

GameObject* Scene::CreateEmpty()
{
	GameObject* gameobject = new GameObject();	//GameObjectを作成
	gameobjects.emplace_back(gameobject);	//リストに追加
	return gameobject;
}

GameObject* Scene::CreateSquare()
{
	GameObject* gameobject = CreateEmpty();	//空のGameObjectを作成
	gameobject->name = "Square";	//名前変更

	ImageRenderer* imageRenderer = gameobject->AddComponent<ImageRenderer>();	//ImageRendererコンポーネント作成
	std::string path = "image/square.png";	//画像のパス
	Image* image = new Image(path);		//画像を読み込み
	imageRenderer->image = image;	//imageをセット
	return gameobject;
}

GameObject* Scene::CreateCamera() 
{
	GameObject* gameobject = CreateEmpty();	//空のGameObjectを作成
	gameobject->name = "Main Camera";	//名前変更

	Camera* camera = gameobject->AddComponent<Camera>();	//Cameraコンポーネント作成
	Scene* scene = SceneManager::GetNowScene();	//Sceneを取得
	return gameobject;
}

//void Scene::DestroyGameObject(GameObject* gameobject)
//{
//	auto iter = std::find(gameobjects.begin(), gameobjects.end(), gameobject);
//}
