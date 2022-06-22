#include "Scene.h"
#include "SceneManager.h"
#include "ImageRenderer.h"
#include "Animator.h"

Scene::Scene()
{
}

void Scene::Init()
{
	treeList = new TreeList(WindowManager::hierarchyWindow, true, this->sceneName);

	CreateCamera();	//カメラ生成
}

void Scene::Update()
{
	for (GameObject* gameobject : gameobjects) {
		gameobject->Update();	//ゲームオブジェクトの更新
		//for (Transform* child : gameobject->transform->children) {
		//	child->Update();
		//}
	}
}

void Scene::Draw(Window* window)
{
	Camera* camera = cameras[this->drawCameraNo];   //現在の対象のCameraを描画
	for (GameObject* gameobject : gameobjects) {
		gameobject->Draw(window, camera);	//ゲームオブジェクトの描画
	}
}

GameObject* Scene::CreateEmpty()
{
	GameObject* gameobject = new GameObject();	//GameObjectを作成
	gameobjects.emplace_back(gameobject);	//リストに追加
	gameobject->SetName(gameobject->GetName() + std::to_string(generateNum));	//名前変更
	generateNum++;	//生成回数加算
	treeList->Add(new TreeNode(gameobject->GetName(), treeList), treeList->GetRoot());	//TreeNodeにも追加
	return gameobject;
}

GameObject* Scene::CreateSquare()
{
	GameObject* gameobject = CreateEmpty();	//空のGameObjectを作成
	gameobject->SetName("Square");	//名前変更

	ImageRenderer* imageRenderer = gameobject->AddComponent<ImageRenderer>();	//ImageRendererコンポーネント作成
	std::string currentPath = "image/square.png";	//画像のパス
	Image* image = new Image(currentPath);		//画像を読み込み
	imageRenderer->image = image;	//imageをセット
	return gameobject;
}

GameObject* Scene::CreateCamera() 
{
	GameObject* gameobject = CreateEmpty();	//空のGameObjectを作成
	gameobject->SetName("Main Camera");	//名前変更

	Camera* camera = gameobject->AddComponent<Camera>();	//Cameraコンポーネント作成
	Scene* scene = SceneManager::GetNowScene();	//Sceneを取得
	return gameobject;
}

void Scene::Destroy(GameObject* gameobject)
{
	std::vector<Transform*> transforms;
	transforms.push_back(gameobject->transform);

	while (transforms.size() != 0) {

		//リストの先頭の要素を取得、削除
		Transform* transform = transforms[0];
		transforms.erase(transforms.begin());

		if (transform->parent) {
			//親にある自身を削除
			std::vector<Transform*>* children = &transform->parent->children;
			children->erase(std::remove(children->begin(), children->end(), transform));
		}

		//シーンから自身を削除
		std::vector<GameObject*>* gameobjects = &SceneManager::GetNowScene()->gameobjects;
		gameobjects->erase(std::remove(gameobjects->begin(), gameobjects->end(), gameobject));

		//子らを追加
		transforms.insert(transforms.end(), transform->children.begin(), transform->children.end());
	}

	//TreeListの要素も削除
	treeList->Delete(gameobject->GetName());
}

//void Scene::RemoveGameObject(GameObject* gameobject)
//{
//	gameobjects.erase(std::remove(gameobjects.begin(), gameobjects.end(), gameobject));
//}

Camera* Scene::GetNowCamera()
{
	return cameras[drawCameraNo];
}


//void Scene::DestroyGameObject(GameObject* gameobject)
//{
//	auto iter = std::find(gameobjects.begin(), gameobjects.end(), gameobject);
//}
