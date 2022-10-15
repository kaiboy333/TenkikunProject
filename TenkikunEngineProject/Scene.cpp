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
	SetName("Scene", false);	//���O������(���͕ς���)
}

void Scene::Update()
{
	std::vector<Collider*> colliders;

	for (GameObject* gameobject : gameobjects) {
		gameobject->Update();	//�Q�[���I�u�W�F�N�g�̍X�V

		std::vector<Collider*> objectColliders = gameobject->GetComponents<Collider>();	//�R���C�_�[�������擾
		colliders.insert(colliders.end(), objectColliders.begin(), objectColliders.end());	//���X�g�Ɉ�C�ɒǉ�
	}

	//�R���C�_�[��2�ȏ゠��Ȃ�
	if ((int)colliders.size() >= 2) {
		for (int i = 0; i < (int)colliders.size(); i++) {
			for (int j = i + 1; j < (int)colliders.size(); j++) {
				//�����Q�[���I�u�W�F�N�g�̃R���C�_�[�Ȃ�
				if (colliders[i]->gameobject == colliders[j]->gameobject) {
					//��΂�
					continue;
				}
				//std::vector<Vector3> crossPoints;

				////�����蔻��ƏՓˉ���
				//if (HitChecker::IsHit(colliders[i], colliders[j], crossPoints)) {
				//	//Debug::Log("Hit!!");
				//	//����������_���R���C�_�[�̌�_���X�g�ɒǉ�
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


	//GameObject�Ȃǂ������Œǉ��A�폜����
	for (auto& addAndRemoveEvent : addAndRemoveEvents) {
		addAndRemoveEvent();
	}
	//���Z�b�g
	addAndRemoveEvents.clear();
}

void Scene::Draw()
{
	Camera* camera = nowCamera;   //���݂̑Ώۂ�Camera��`��
	for (GameObject* gameobject : gameobjects) {
		gameobject->Draw();	//�Q�[���I�u�W�F�N�g�̕`��
	}
}

GameObject* Scene::CreateEmpty(bool isLaterAdd)
{
	GameObject* gameobject = new GameObject();	//GameObject���쐬
	gameobject->transform = gameobject->AddComponent<Transform>();	//Transform������
	TreeNode* node = new TreeNode(gameobject->GetName(), treeList, treeList->isFirstOpen);
	//�E�N���b�N����������
	node->mouseRightClickEvents.push_back(std::make_pair(node->GetEventNo(), [node, this, gameobject](void) {
		Vector3 mousePos = Input::GetMousePosition();

		MenuList* menuList0 = new MenuList(mousePos.x, mousePos.y, { "Rename(��)", "Delete", "B", "C" });
		//WindowManager�ɃZ�b�g
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
		GameObject* gameobject = GameObject::Find(node->GetElement());	//���̃m�[�h�̖��O����Q�[���I�u�W�F�N�g�擾
		//���������Ȃ�
		if (gameobject) {
			WindowManager::inspectorWindow->SetGameObject(gameobject);	//�Q�[���I�u�W�F�N�g�̏����q�G�����L�[�ɃZ�b�g
		}
	}));
	treeList->Add(node, treeList->GetRoot());	//TreeNode�ɂ��ǉ�
	if (isLaterAdd) {
		//���ƂŒǉ�
		addAndRemoveEvents.push_back([this, gameobject](void) {
			gameobject->SetName("GameObject");	//���O�ύX(�����̖��O)
			gameobjects.emplace_back(gameobject);	//���X�g�ɒǉ�
		});
	}
	else {
		//�����ɒǉ�
		gameobject->SetName("GameObject");	//���O�ύX(�����̖��O)
		gameobjects.emplace_back(gameobject);	//���X�g�ɒǉ�
	}
	return gameobject;
}

GameObject* Scene::CreateSquare(bool isLaterAdd)
{
	GameObject* gameobject = CreateEmpty(isLaterAdd);	//���GameObject���쐬
	if (isLaterAdd) {
		//���Ƃ�
		addAndRemoveEvents.push_back([this, gameobject](void) {
			gameobject->SetName("Square");	//���O�ύX
		});
	}
	else {
		//������
		gameobject->SetName("Square");	//���O�ύX
	}

	ImageRenderer* imageRenderer = gameobject->AddComponent<ImageRenderer>();	//ImageRenderer�R���|�[�l���g�쐬
	Component* component = static_cast<Component*>(imageRenderer);
	//�l�p�̉摜��T��
	for (std::pair<std::string, std::filesystem::path> pair : ProjectFileManager::guidAndPath) {
		if (pair.second.string() == ProjectFileManager::resourceFilePath.string() + "\\Square.png") {
			imageRenderer->image = static_cast<Image*>(ProjectFileManager::pathAndInfo[pair.second]);	//image���Z�b�g
			break;
		}
	}

	BoxCollider* boxCollider = gameobject->AddComponent<BoxCollider>();	//BoxCollider�쐬

	return gameobject;
}

GameObject* Scene::CreateCircle(bool isLaterAdd)
{
	GameObject* gameobject = CreateEmpty(isLaterAdd);	//���GameObject���쐬
	if (isLaterAdd) {
		//���Ƃ�
		addAndRemoveEvents.push_back([this, gameobject](void) {
			gameobject->SetName("Circle");	//���O�ύX
		});
	}
	else {
		//������
		gameobject->SetName("Circle");	//���O�ύX
	}
	gameobject->transform->scale = Vector3(0.3f, 0.3f, 1);	//�T�C�Y�ύX

	ImageRenderer* imageRenderer = gameobject->AddComponent<ImageRenderer>();	//ImageRenderer�R���|�[�l���g�쐬
	Component* component = static_cast<Component*>(imageRenderer);
	//�~�̉摜��T��
	for (std::pair<std::string, std::filesystem::path> pair : ProjectFileManager::guidAndPath) {
		if (pair.second.string() == ProjectFileManager::resourceFilePath.string() + "\\Circle.png") {
			imageRenderer->image = static_cast<Image*>(ProjectFileManager::pathAndInfo[pair.second]);	//image���Z�b�g
			break;
		}
	}

	CircleCollider* circleCollider = gameobject->AddComponent<CircleCollider>();	//CircleCollider�쐬

	return gameobject;
}

GameObject* Scene::CreateCamera(bool isLaterAdd)
{
	GameObject* gameobject = CreateEmpty(isLaterAdd);	//���GameObject���쐬
	if (isLaterAdd) {
		//���Ƃ�
		addAndRemoveEvents.push_back([this, gameobject](void) {
			gameobject->SetName("MainCamera");	//���O�ύX
		});
	}
	else {
		//������
		gameobject->SetName("MainCamera");	//���O�ύX
	}

	Camera* camera = gameobject->AddComponent<Camera>();	//Camera�R���|�[�l���g�쐬
	SetNowCamera(camera);	//���݂̃J�����ɂ�����Z�b�g
	Scene* scene = SceneManager::GetNowScene();	//Scene���擾
	return gameobject;
}

GameObject* Scene::CreateTenkikun(bool isLaterAdd)
{
	GameObject* gameobject = CreateEmpty(isLaterAdd);	//���GameObject���쐬
	if (isLaterAdd) {
		//���Ƃ�
		addAndRemoveEvents.push_back([this, gameobject](void) {
			gameobject->SetName("Tenkikun");	//���O�ύX
		});
	}
	else {
		//������
		gameobject->SetName("Tenkikun");	//���O�ύX
	}

	ImageRenderer* imageRenderer = gameobject->AddComponent<ImageRenderer>();	//ImageRenderer�R���|�[�l���g�쐬
	//Component* component = static_cast<Component*>(imageRenderer);
	//�V�C����̉摜��T��
	for (std::pair<std::string, std::filesystem::path> pair : ProjectFileManager::guidAndPath) {
		if (pair.second.string() == ProjectFileManager::resourceFilePath.string() + "\\Tenkikun.png") {
			imageRenderer->image = static_cast<Image*>(ProjectFileManager::pathAndInfo[pair.second]);	//image���Z�b�g
			break;
		}
	}

	gameobject->AddComponent<BoxCollider>();	//BoxCollider�쐬

	return gameobject;
}

GameObject* Scene::CreateUnityChan(bool isLaterAdd)
{
	GameObject* gameobject = CreateEmpty(isLaterAdd);	//���GameObject���쐬
	if (isLaterAdd) {
		//���Ƃ�
		addAndRemoveEvents.push_back([this, gameobject](void) {
			gameobject->SetName("UnityChan");	//���O�ύX
		});
	}
	else {
		//������
		gameobject->SetName("UnityChan");	//���O�ύX
	}

	ImageRenderer* imageRenderer = gameobject->AddComponent<ImageRenderer>();	//ImageRenderer�R���|�[�l���g�쐬
	Animator* animator = gameobject->AddComponent<Animator>();	//Animator�R���|�[�l���g�쐬

	//�A�j���[�V�����R���g���[���[�̍쐬
	std::filesystem::path acPath = ProjectFileManager::currentPath.string() + "\\" + "PlayerAnimatorController" + ".animctr";
	AnimatorController* ac = new AnimatorController(acPath);

	animator->ac = ac;	//Animator��ac���Z�b�g
	ac->AddFloatParamater("isSpeed", 0.0f);	//�p�����[�^�[���Z�b�g

	//�ҋ@�A�j���[�V�����̃Z�b�g
	//�ҋ@�A�j���[�V�����̍쐬
	std::filesystem::path idleAnimPath = ProjectFileManager::currentPath.string() + "\\" + "IdleAnimation" + ".anim";
	Animation* idleAnim = new Animation(idleAnimPath);

	//�ҋ@�摜�̍쐬
	std::vector<Image*> idleImages;
	for (int i = 0; i < 3; i++) {
		idleImages.push_back(static_cast<Image*>(ProjectFileManager::pathAndInfo[ProjectFileManager::resourceFilePath.string() + "\\UnityChan_Idle" + std::to_string(i) + ".png"]));
	}
	//�A�j���[�V�����L�[�Ƃ��Ēǉ�
	idleAnim->AddAnimationKey(idleImages, 10);
	//ac�ɃA�j���[�V�������Z�b�g����State���擾
	AnimationState* idleState = animator->AddState(idleAnim, "Idle");

	//����A�j���[�V�����̃Z�b�g
	//�ҋ@�A�j���[�V�����̍쐬
	std::filesystem::path runAnimPath = ProjectFileManager::currentPath.string() + "\\" + "RunAnimation" + ".anim";
	Animation* runAnim = new Animation(runAnimPath);
	
	//����摜�̍쐬
	std::vector<Image*> runImages;
	for (int i = 0; i < 8; i++) {
		runImages.push_back(static_cast<Image*>(ProjectFileManager::pathAndInfo[ProjectFileManager::resourceFilePath.string() + "\\UnityChan_Run" + std::to_string(i) + ".png"]));
	}
	//�A�j���[�V�����L�[�Ƃ��Ēǉ�
	runAnim->AddAnimationKey(runImages, 7);
	//ac�ɃA�j���[�V�������Z�b�g����State���擾
	AnimationState* runState = animator->AddState(runAnim, "Run");

	//Transition�쐬
	//�ҋ@State��Transition�ǉ�
	AnimationTransition* idleToRun = idleState->AddTransition(runState);
	idleToRun->AddCondition("isSpeed", 1.0, AnimationCondition::Mode::Greater);
	//����State��Transition�ǉ�
	AnimationTransition* runToIdle = runState->AddTransition(idleState);
	runToIdle->AddCondition("isSpeed", 1.0, AnimationCondition::Mode::Less);

	gameobject->AddComponent<BoxCollider>();	//BoxCollider�쐬

	gameobject->AddComponent<RigidBody>();	//RigidBody�쐬

	gameobject->AddComponent<PlayerScript>();	//Script�쐬

	return gameobject;
}

void Scene::Destroy(GameObject* gameobject)
{
	std::vector<Transform*> transforms;
	transforms.push_back(gameobject->transform);

	while (transforms.size() != 0) {

		//���X�g�̐擪�̗v�f���擾�A�폜
		Transform* transform = transforms[0];
		transforms.erase(transforms.begin());

		if (transform->parent) {
			//�e�ɂ��鎩�g���폜
			std::vector<Transform*>* children = &transform->parent->children;
			//children->erase(std::remove(children->begin(), children->end(), transform));
		}

		//�V�[�����玩�g���폜
		std::vector<GameObject*>* gameobjects = &SceneManager::GetNowScene()->gameobjects;
		gameobjects->erase(std::remove(gameobjects->begin(), gameobjects->end(), gameobject));

		//�q���ǉ�
		transforms.insert(transforms.end(), transform->children.begin(), transform->children.end());
	}

	//TreeList�̗v�f���폜
	treeList->Delete(gameobject->GetPath());
}

void Scene::SetNowCamera(Camera* camera)
{
	//���X�g�ɂȂ��Ȃ�ǉ�
	AddCamera(camera);
	//������Z�b�g
	nowCamera = camera;
}

Camera* Scene::GetNowCamera()
{
	return nowCamera;
}

void Scene::AddCamera(Camera* camera)
{
	//���X�g������ۂł͂Ȃ��Ȃ�
	if (cameras.size() != 0) {
		//���X�g�ɃJ���������݂��Ȃ��Ȃ�
		if (!(*std::find(cameras.begin(), cameras.end(), camera) == camera)) {
			//���X�g�ɒǉ�
			cameras.push_back(camera);
		}
	}
	else {
		//���X�g�ɒǉ�
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
	//�V�[���p�X�̃}�b�v���擾
	std::map<std::string, std::filesystem::path>& map = SceneManager::scenePathes;

	//�����ł��̖��O�ɂ��Ȃ��Ȃ�
	if (!isForce) {
		int no = 1;	//���h�~�p�ԍ�
		//���Ȃ��Ȃ�܂ŌJ��Ԃ�
		while (map.contains(name)) {
			name = name + " (" + std::to_string(no++) + ")";	//�V�������̖��O���쐬
		}
	}

	//TreeList�̖��O��ς���
	TreeList* treeList = SceneManager::GetNowScene()->treeList;
	TreeNode* node = treeList->GetRoot();	//���[�g�m�[�h�擾
	if (node) {
		//���O�Z�b�g
		node->SetElement(name);
	}

	if (!isForce) {
		//���ɑO�̖��O���o�^����Ă���Ȃ�
		if (map.contains(this->name)) {
			//�V�[���p�X�̃t�@�C��������菜���������擾
			std::string removedFileName = map[this->name].string().substr(0, map[this->name].string().length() - map[this->name].filename().string().length());
			//�ύX��̖��O�擾
			std::filesystem::path afterPath = removedFileName + name + ".scene";
			//�V�[���t�@�C���̖��O���ύX
			std::filesystem::rename(map[this->name], afterPath);

			//�V�[���p�X�̑O�̂��폜
			map.erase(map.find(this->name));
			//�V�[���p�X�̐V�����̂�ǉ�(����Ŏ�������ւ�)
			map.insert(std::make_pair(name, afterPath));
		}
	}
	this->name = name;	//���ۂɕς���
}

//void Scene::DestroyGameObject(GameObject* gameobject)
//{
//	auto iter = std::find(gameobjects.begin(), gameobjects.end(), gameobject);
//}
