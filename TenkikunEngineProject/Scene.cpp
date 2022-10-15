#include "Scene.h"
#include "SceneManager.h"
#include "ImageRenderer.h"
#include "Animator.h"
#include "ProjectFileManager.h"
#include "Debug.h"
#include "Collider.h"
#include "HitChecker.h"
#include "RigidBody.h"
#include "PlayerScript.h"
#include "GJK.h"

void Scene::Init()
{
	Window* window = WindowManager::hierarchyWindow;
	treeList = new TreeList(window->startX, window->startY, window->width, window->height, true, true, this->name);
	SetName("Scene", false);	//名前初期化(被りは変える)
}

void Scene::Update()
{
	std::vector<Collider*> colliders;

	for (GameObject* gameobject : gameobjects) {
		gameobject->Update();	//ゲームオブジェクトの更新

		std::vector<Collider*> objectColliders = gameobject->GetComponents<Collider>();	//コライダーたちを取得
		colliders.insert(colliders.end(), objectColliders.begin(), objectColliders.end());	//リストに一気に追加
	}

	//コライダーが2つ以上あるなら
	if ((int)colliders.size() >= 2) {
		for (int i = 0; i < (int)colliders.size(); i++) {
			for (int j = i + 1; j < (int)colliders.size(); j++) {
				//同じゲームオブジェクトのコライダーなら
				if (colliders[i]->gameobject == colliders[j]->gameobject) {
					//飛ばす
					continue;
				}
				//std::vector<Vector3> crossPoints;

				////当たり判定と衝突応答
				//if (HitChecker::IsHit(colliders[i], colliders[j], crossPoints)) {
				//	//Debug::Log("Hit!!");
				//	//当たった交点をコライダーの交点リストに追加
				//	colliders[i]->crossPoints.insert(colliders[i]->crossPoints.end(), crossPoints.begin(), crossPoints.end());
				//	colliders[j]->crossPoints.insert(colliders[j]->crossPoints.end(), crossPoints.begin(), crossPoints.end());
				//}

				if (GJK::IsHit(colliders[i], colliders[j])) {
					colliders[i]->isHit = true;
					colliders[j]->isHit = true;
				}
				//if (GJK::IsHit2(colliders[i])) {
				//	colliders[i]->isHit = true;
				//}
				//if (GJK::IsHit2( colliders[j])) {
				//	colliders[j]->isHit = true;
				//}
			}
		}
	}

	//Vector2 crossPoint;
	//Vector2 vec1 = Vector2(-50, -10), vec2 = Vector2(50, -10), vec3 = Vector2::Zero();
	//Vector2::GetMinDistance(vec1, vec2, vec3, crossPoint);
	//vec1.DrawPoint();
	//vec2.DrawPoint();
	//vec3.DrawPoint();
	//crossPoint.DrawPoint(GetColor(255, 0, 0));
	//ScreenFlip();


	//GameObjectなどをここで追加、削除する
	for (auto& addAndRemoveEvent : addAndRemoveEvents) {
		addAndRemoveEvent();
	}
	//リセット
	addAndRemoveEvents.clear();
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
	GameObject* gameobject = new GameObject();	//GameObjectを作成
	gameobject->transform = gameobject->AddComponent<Transform>();	//Transformをついか
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
	node->mouseDoubleClickEvents.push_back(std::make_pair(node->GetEventNo(), [node](void) {
		GameObject* gameobject = GameObject::Find(node->GetElement());	//このノードの名前からゲームオブジェクト取得
		//見つかったなら
		if (gameobject) {
			WindowManager::inspectorWindow->SetGameObject(gameobject);	//ゲームオブジェクトの情報をヒエラルキーにセット
		}
	}));
	treeList->Add(node, treeList->GetRoot());	//TreeNodeにも追加
	if (isLaterAdd) {
		//あとで追加
		addAndRemoveEvents.push_back([this, gameobject](void) {
			gameobject->SetName("GameObject");	//名前変更(初期の名前)
			gameobjects.emplace_back(gameobject);	//リストに追加
		});
	}
	else {
		//すぐに追加
		gameobject->SetName("GameObject");	//名前変更(初期の名前)
		gameobjects.emplace_back(gameobject);	//リストに追加
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

	gameobject->AddComponent<RigidBody>();	//RigidBody作成

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
	treeList->Delete(gameobject->GetPath());
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
	this->name = name;	//実際に変える
}

//void Scene::DestroyGameObject(GameObject* gameobject)
//{
//	auto iter = std::find(gameobjects.begin(), gameobjects.end(), gameobject);
//}
