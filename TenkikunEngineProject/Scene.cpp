#include "Scene.h"
#include "SceneManager.h"
#include "ImageRenderer.h"
#include "Animator.h"
#include "ProjectFileManager.h"
#include "Debug.h"
#include "Collider.h"
#include "HitManager.h"
#include "RigidBody.h"
#include "PlayerScript.h"
#include "GJK.h"
#include "BoxCollider.h"

//void Scene::Init()
//{
//	Window* window = WindowManager::hierarchyWindow;
//	treeList = new TreeList(window->startX, window->startY, window->width, window->height, true, true, this->name);
//	SetName("Scene", false);	//名前初期化(被りは変える)
//}

Scene::Scene()
{
	//インスペクターのリセット
	WindowManager::inspectorWindow->PreparationLibrate();
}

void Scene::Update()
{
	//GameObjectなどをここで追加、削除する
	for (auto& addAndRemoveEvent : addAndRemoveEvents) {
		addAndRemoveEvent();
	}
	//リセット
	addAndRemoveEvents.clear();

	//プレイ中でないならここで終わり
	if (SceneManager::playMode != SceneManager::PlayMode::PLAY)
		return;

	for (GameObject* gameobject : gameobjects) {
		gameobject->Update();	//ゲームオブジェクトの更新
	}

	//当たり判定のチェック
	HitManager hitManager = HitManager();
	hitManager.HitCheck();
	hitManager.CallHitFunction(beforeOnCollisions, beforeOnTriggers);
}

void Scene::Draw()
{
	Camera* camera = nowCamera;   //現在の対象のCameraを描画
	for (GameObject* gameobject : gameobjects) {
		gameobject->Draw();	//ゲームオブジェクトの描画
	}
}

GameObject* Scene::CreateEmpty(bool isLaterAdd)
{
	TreeList* treeList = WindowManager::hierarchyWindow->treeList;

	GameObject* gameobject = new GameObject();	//GameObjectを作成
	gameobject->SetScene(this);	//シーンをセット
	gameobject->transform = gameobject->AddComponent<Transform>();	//Transformをついか
	//シーンが同じなら
	if (SceneManager::GetNowScene() == this) {
		TreeNode* node = new TreeNode(gameobject->GetName(), treeList, treeList->isFirstOpen);
		//右クリックを押したら
		node->mouseRightClickEvents.push_back(std::make_pair(node->GetEventNo(), [node, this, gameobject](void) {
			Vector3 mousePos = Input::GetMousePosition();

			MenuList* menuList0 = new MenuList(mousePos.x, mousePos.y, { "Rename(仮)", "Delete", "B", "C" });
			//WindowManagerにセット
			WindowManager::SetMenuList(menuList0);

			MenuNode* menuNode0_0 = menuList0->FindNode("Rename");
			//menuNode0_0->mouseClickDownEvents.insert(menuNode0_0->mouseClickDownEvents.begin(), std::make_pair(menuNode0_0->GetEventNo(), [this, gameobject]() {
			//	
			//}));
			MenuNode* menuNode0_1 = menuList0->FindNode("Delete");
			menuNode0_1->mouseClickDownEvents.insert(menuNode0_1->mouseClickDownEvents.begin(), std::make_pair(menuNode0_1->GetEventNo(), [this, gameobject]() {
				Destroy(gameobject);
			}));
		}));
		node->mouseDoubleClickEvents.push_back(std::make_pair(node->GetEventNo(), [node, gameobject](void) {
			if (gameobject) {
				WindowManager::inspectorWindow->SetGameObject(gameobject);	//ゲームオブジェクトの情報をヒエラルキーにセット
			}
		}));

		if (isLaterAdd) {
			//あとで追加
			addAndRemoveEvents.push_back([this, gameobject, treeList, node](void) {
				gameobject->SetName("GameObject");	//名前変更(初期の名前)
				gameobjects.emplace_back(gameobject);	//リストに追加
				treeList->Add(node, treeList->GetRoot());	//TreeListにも追加
			});
		}
		else {
			//すぐに追加
			gameobject->SetName("GameObject");	//名前変更(初期の名前)
			gameobjects.emplace_back(gameobject);	//リストに追加
			treeList->Add(node, treeList->GetRoot());	//TreeListにも追加
		}
	}

	return gameobject;
}

GameObject* Scene::CreateSquare(bool isLaterAdd)
{
	GameObject* gameobject = CreateEmpty(isLaterAdd);	//空のGameObjectを作成
	if (isLaterAdd) {
		//あとで
		addAndRemoveEvents.push_back([this, gameobject](void) {
			gameobject->SetName("Square");	//名前変更
		});
	}
	else {
		//すぐに
		gameobject->SetName("Square");	//名前変更
	}

	ImageRenderer* imageRenderer = gameobject->AddComponent<ImageRenderer>();	//ImageRendererコンポーネント作成
	Component* component = static_cast<Component*>(imageRenderer);
	//四角の画像を探す
	for (std::pair<std::string, std::filesystem::path> pair : ProjectFileManager::guidAndPath) {
		if (pair.second.string() == ProjectFileManager::resourceFilePath.string() + "\\Square.png") {
			imageRenderer->image = static_cast<Image*>(ProjectFileManager::pathAndInfo[pair.second]);	//imageをセット
			break;
		}
	}

	BoxCollider* boxCollider = gameobject->AddComponent<BoxCollider>();	//BoxCollider作成

	return gameobject;
}

GameObject* Scene::CreateCircle(bool isLaterAdd)
{
	GameObject* gameobject = CreateEmpty(isLaterAdd);	//空のGameObjectを作成
	if (isLaterAdd) {
		//あとで
		addAndRemoveEvents.push_back([this, gameobject](void) {
			gameobject->SetName("Circle");	//名前変更
		});
	}
	else {
		//すぐに
		gameobject->SetName("Circle");	//名前変更
	}
	gameobject->transform->scale = Vector3(0.3f, 0.3f, 1);	//サイズ変更

	ImageRenderer* imageRenderer = gameobject->AddComponent<ImageRenderer>();	//ImageRendererコンポーネント作成
	Component* component = static_cast<Component*>(imageRenderer);
	//円の画像を探す
	for (std::pair<std::string, std::filesystem::path> pair : ProjectFileManager::guidAndPath) {
		if (pair.second.string() == ProjectFileManager::resourceFilePath.string() + "\\Circle.png") {
			imageRenderer->image = static_cast<Image*>(ProjectFileManager::pathAndInfo[pair.second]);	//imageをセット
			break;
		}
	}

	CircleCollider* circleCollider = gameobject->AddComponent<CircleCollider>();	//CircleCollider作成

	return gameobject;
}

GameObject* Scene::CreateCamera(bool isLaterAdd)
{
	GameObject* gameobject = CreateEmpty(isLaterAdd);	//空のGameObjectを作成
	if (isLaterAdd) {
		//あとで
		addAndRemoveEvents.push_back([this, gameobject](void) {
			gameobject->SetName("MainCamera");	//名前変更
		});
	}
	else {
		//すぐに
		gameobject->SetName("MainCamera");	//名前変更
	}

	Camera* camera = gameobject->AddComponent<Camera>();	//Cameraコンポーネント作成
	SetNowCamera(camera);	//現在のカメラにこれをセット
	Scene* scene = SceneManager::GetNowScene();	//Sceneを取得
	return gameobject;
}

GameObject* Scene::CreateTenkikun(bool isLaterAdd)
{
	GameObject* gameobject = CreateEmpty(isLaterAdd);	//空のGameObjectを作成
	if (isLaterAdd) {
		//あとで
		addAndRemoveEvents.push_back([this, gameobject](void) {
			gameobject->SetName("Tenkikun");	//名前変更
		});
	}
	else {
		//すぐに
		gameobject->SetName("Tenkikun");	//名前変更
	}

	ImageRenderer* imageRenderer = gameobject->AddComponent<ImageRenderer>();	//ImageRendererコンポーネント作成
	//Component* component = static_cast<Component*>(imageRenderer);
	//天気くんの画像を探す
	for (std::pair<std::string, std::filesystem::path> pair : ProjectFileManager::guidAndPath) {
		if (pair.second.string() == ProjectFileManager::resourceFilePath.string() + "\\Tenkikun.png") {
			imageRenderer->image = static_cast<Image*>(ProjectFileManager::pathAndInfo[pair.second]);	//imageをセット
			break;
		}
	}

	gameobject->AddComponent<BoxCollider>();	//BoxCollider作成

	return gameobject;
}

GameObject* Scene::CreateUnityChan(bool isLaterAdd)
{
	GameObject* gameobject = CreateEmpty(isLaterAdd);	//空のGameObjectを作成
	if (isLaterAdd) {
		//あとで
		addAndRemoveEvents.push_back([this, gameobject](void) {
			gameobject->SetName("UnityChan");	//名前変更
		});
	}
	else {
		//すぐに
		gameobject->SetName("UnityChan");	//名前変更
	}

	ImageRenderer* imageRenderer = gameobject->AddComponent<ImageRenderer>();	//ImageRendererコンポーネント作成
	Animator* animator = gameobject->AddComponent<Animator>();	//Animatorコンポーネント作成

	//アニメーションコントローラーの作成
	std::filesystem::path acPath = ProjectFileManager::currentPath.string() + "\\" + "PlayerAnimatorController" + ".animctr";
	AnimatorController* ac = new AnimatorController(acPath);

	animator->ac = ac;	//Animatorにacをセット
	ac->AddFloatParamater("isSpeed", 0.0f);	//パラメーターをセット

	//待機アニメーションのセット
	//待機アニメーションの作成
	std::filesystem::path idleAnimPath = ProjectFileManager::currentPath.string() + "\\" + "IdleAnimation" + ".anim";
	Animation* idleAnim = new Animation(idleAnimPath);

	//待機画像の作成
	std::vector<Image*> idleImages;
	for (int i = 0; i < 3; i++) {
		idleImages.push_back(static_cast<Image*>(ProjectFileManager::pathAndInfo[ProjectFileManager::resourceFilePath.string() + "\\UnityChan_Idle" + std::to_string(i) + ".png"]));
	}
	//アニメーションキーとして追加
	idleAnim->AddAnimationKey(idleImages, 10);
	//acにアニメーションをセットしてStateを取得
	AnimationState* idleState = animator->AddState(idleAnim, "Idle");

	//走るアニメーションのセット
	//待機アニメーションの作成
	std::filesystem::path runAnimPath = ProjectFileManager::currentPath.string() + "\\" + "RunAnimation" + ".anim";
	Animation* runAnim = new Animation(runAnimPath);
	
	//走る画像の作成
	std::vector<Image*> runImages;
	for (int i = 0; i < 8; i++) {
		runImages.push_back(static_cast<Image*>(ProjectFileManager::pathAndInfo[ProjectFileManager::resourceFilePath.string() + "\\UnityChan_Run" + std::to_string(i) + ".png"]));
	}
	//アニメーションキーとして追加
	runAnim->AddAnimationKey(runImages, 7);
	//acにアニメーションをセットしてStateを取得
	AnimationState* runState = animator->AddState(runAnim, "Run");

	//Transition作成
	//待機StateのTransition追加
	AnimationTransition* idleToRun = idleState->AddTransition(runState);
	idleToRun->AddCondition("isSpeed", 1.0, AnimationCondition::Mode::Greater);
	//走るStateのTransition追加
	AnimationTransition* runToIdle = runState->AddTransition(idleState);
	runToIdle->AddCondition("isSpeed", 1.0, AnimationCondition::Mode::Less);

	gameobject->AddComponent<BoxCollider>();	//BoxCollider作成

	auto rb = gameobject->AddComponent<RigidBody>();	//RigidBody作成
	rb->constraints.freezeRotation.z = true;

	gameobject->AddComponent<PlayerScript>();	//Script作成

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
			//children->erase(std::remove(children->begin(), children->end(), transform));
		}

		//シーンから自身を削除
		std::vector<GameObject*>* gameobjects = &SceneManager::GetNowScene()->gameobjects;
		gameobjects->erase(std::remove(gameobjects->begin(), gameobjects->end(), gameobject));

		//子らを追加
		transforms.insert(transforms.end(), transform->children.begin(), transform->children.end());
	}

	//TreeListの要素も削除
	WindowManager::hierarchyWindow->treeList->Delete(gameobject->GetPath());
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
	std::map<std::string, std::filesystem::path>& map = SceneManager::scenePathes;

	//名前の候補決め
	std::string newName = name;
	if (!isForce) {
		int no = 1;	//被り防止用番号
		//被らなくなるまで繰り返す
		while (map.contains(newName)) {
			newName = name + " (" + std::to_string(no++) + ")";	//新しい候補の名前を作成
		}
	}

	//TreeListの名前を変える
	TreeNode* node = WindowManager::hierarchyWindow->treeList->GetRoot();	//ルート取得
	if (node) {
		//名前セット
		node->SetElement(name);
	}

	if (!isForce) {
		//既に前の名前が登録されているなら
		if (map.contains(this->name)) {
			//シーンパスのファイル名を取り除いた文字取得
			std::string removedFileName = map[this->name].string().substr(0, map[this->name].string().length() - map[this->name].filename().string().length());
			//変更後の名前取得
			std::filesystem::path afterPath = removedFileName + name + ".scene";
			//シーンファイルの名前も変更
			std::filesystem::rename(map[this->name], afterPath);

			//シーンパスの前のを削除
			map.erase(map.find(this->name));
			//シーンパスの新しいのを追加(これで実質入れ替え)
			map.insert(std::make_pair(name, afterPath));
		}
	}
	this->name = newName;	//実際に変える
}

void Scene::PreparationLibrate()
{
	nowCamera = nullptr;
	cameras.clear();

	for (auto& gameobject : gameobjects) {
		//gameobjectの解放準備
		gameobject->PreparationLibrate();
		//解放
		delete(gameobject);
		gameobject = nullptr;
	}
	gameobjects.clear();

	//sceneInfosから削除
	ProjectFileManager::sceneInfos.erase(this->fileID);
}

GameObject* Scene::Find(std::string name)
{
	for (GameObject* gameobject : this->gameobjects) {
		if (gameobject->GetName() == name) {
			return gameobject;
		}
	}
	return nullptr;
}

//void Scene::DestroyGameObject(GameObject* gameobject)
//{
//	auto iter = std::find(gameobjects.begin(), gameobjects.end(), gameobject);
//}
