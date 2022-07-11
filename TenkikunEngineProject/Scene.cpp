#include "Scene.h"
#include "SceneManager.h"
#include "ImageRenderer.h"
#include "Animator.h"
#include "ProjectFileManager.h"
#include "Debug.h"

Scene::Scene()
{

}

void Scene::Init()
{
	Window* window = WindowManager::hierarchyWindow;
	treeList = new TreeList(window->startX, window->startY, window->width, window->height, window, true, true, this->name);
	SetName("Scene", false);	//名前初期化(被りは変える)
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

void Scene::Draw(Window* parentWindow)
{
	Camera* camera = nowCamera;   //現在の対象のCameraを描画
	for (GameObject* gameobject : gameobjects) {
		gameobject->Draw(parentWindow, camera);	//ゲームオブジェクトの描画
	}
}

GameObject* Scene::CreateEmpty()
{
	GameObject* gameobject = new GameObject();	//GameObjectを作成
	gameobject->transform = gameobject->AddComponent<Transform>();	//Transformをついか
	gameobjects.emplace_back(gameobject);	//リストに追加
	gameobject->SetName("GameObject");	//名前変更(初期の名前)
	treeList->Add(new TreeNode(gameobject->GetName(), treeList, treeList->isFirstOpen), treeList->GetRoot());	//TreeNodeにも追加
	return gameobject;
}

GameObject* Scene::CreateSquare()
{
	GameObject* gameobject = CreateEmpty();	//空のGameObjectを作成
	gameobject->SetName("Square");	//名前変更

	ImageRenderer* imageRenderer = gameobject->AddComponent<ImageRenderer>();	//ImageRendererコンポーネント作成
	Component* component = static_cast<Component*>(imageRenderer);
	//四角の画像を探す
	for (Image* image : ProjectFileManager::GetSpecificInfos<Image>()) {
		if (image->GetPath().string() == ProjectFileManager::resourceFilePath.string() + "\\Square.png") {
			imageRenderer->image = image;	//imageをセット
			break;
		}
	}
	return gameobject;
}

GameObject* Scene::CreateCamera() 
{
	GameObject* gameobject = CreateEmpty();	//空のGameObjectを作成
	gameobject->SetName("Main Camera");	//名前変更

	Camera* camera = gameobject->AddComponent<Camera>();	//Cameraコンポーネント作成
	SetNowCamera(camera);	//現在のカメラにこれをセット
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

void Scene::SetNowCamera(Camera* camera)
{
	//リストにないなら追加
	AddCamera(camera);
	//それをセット
	nowCamera = camera;
}

Camera* Scene::GetNowCamera()
{
	return nowCamera;
}

void Scene::AddCamera(Camera* camera)
{
	//リストが空っぽではないなら
	if (cameras.size() != 0) {
		//リストにカメラが存在しないなら
		if (!(*std::find(cameras.begin(), cameras.end(), camera) == camera)) {
			//リストに追加
			cameras.push_back(camera);
		}
	}
	else {
		//リストに追加
		cameras.push_back(camera);
	}
}

std::vector<Camera*> Scene::GetCameras()
{
	return cameras;
}

std::string Scene::GetName()
{
	return name;
}

void Scene::SetName(std::string name, bool isForce)
{
	//シーンパスのマップを取得
	std::unordered_map<std::string, std::filesystem::path>& map = SceneManager::scenePathes;

	//強制でその名前にしないなら
	if (!isForce) {
		int no = 1;	//被り防止用番号
		//被らなくなるまで繰り返す
		while (map.contains(name)) {
			name = name + " (" + std::to_string(no++) + ")";	//新しい候補の名前を作成
		}
	}

	//TreeListの名前を変える
	TreeList* treeList = SceneManager::GetNowScene()->treeList;
	TreeNode* node = treeList->GetRoot();	//ルートノード取得
	if (node) {
		//名前セット
		node->SetElement(name);
	}

	if (!isForce) {
		//既に前の名前が登録されているなら
		if (map.contains(this->name)) {
			//シーンパスのマップの名前を変える(置き換え)
			map.insert_or_assign(map.find(this->name), name, map[this->name]);
		}
	}
	this->name = name;	//実際に変える
}

//void Scene::DestroyGameObject(GameObject* gameobject)
//{
//	auto iter = std::find(gameobjects.begin(), gameobjects.end(), gameobject);
//}
