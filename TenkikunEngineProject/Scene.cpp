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
//	SetName("Scene", false);	//���O������(���͕ς���)
//}

Scene::Scene()
{
	//�C���X�y�N�^�[�̃��Z�b�g
	WindowManager::inspectorWindow->PreparationLibrate();
}

void Scene::Update()
{
	//GameObject�Ȃǂ������Œǉ��A�폜����
	for (auto& addAndRemoveEvent : addAndRemoveEvents) {
		addAndRemoveEvent();
	}
	//���Z�b�g
	addAndRemoveEvents.clear();

	//�v���C���łȂ��Ȃ炱���ŏI���
	if (SceneManager::playMode != SceneManager::PlayMode::PLAY)
		return;

	for (GameObject* gameobject : gameobjects) {
		gameobject->Update();	//�Q�[���I�u�W�F�N�g�̍X�V
	}

	//�����蔻��̃`�F�b�N
	HitManager hitManager = HitManager();
	hitManager.HitCheck();
	hitManager.CallHitFunction(beforeOnCollisions, beforeOnTriggers);
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
	TreeList* treeList = WindowManager::hierarchyWindow->treeList;

	GameObject* gameobject = new GameObject();	//GameObject���쐬
	gameobject->SetScene(this);	//�V�[�����Z�b�g
	gameobject->transform = gameobject->AddComponent<Transform>();	//Transform������
	//�V�[���������Ȃ�
	if (SceneManager::GetNowScene() == this) {
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
		node->mouseDoubleClickEvents.push_back(std::make_pair(node->GetEventNo(), [node, gameobject](void) {
			if (gameobject) {
				WindowManager::inspectorWindow->SetGameObject(gameobject);	//�Q�[���I�u�W�F�N�g�̏����q�G�����L�[�ɃZ�b�g
			}
		}));

		if (isLaterAdd) {
			//���ƂŒǉ�
			addAndRemoveEvents.push_back([this, gameobject, treeList, node](void) {
				gameobject->SetName("GameObject");	//���O�ύX(�����̖��O)
				gameobjects.emplace_back(gameobject);	//���X�g�ɒǉ�
				treeList->Add(node, treeList->GetRoot());	//TreeList�ɂ��ǉ�
			});
		}
		else {
			//�����ɒǉ�
			gameobject->SetName("GameObject");	//���O�ύX(�����̖��O)
			gameobjects.emplace_back(gameobject);	//���X�g�ɒǉ�
			treeList->Add(node, treeList->GetRoot());	//TreeList�ɂ��ǉ�
		}
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

	auto rb = gameobject->AddComponent<RigidBody>();	//RigidBody�쐬
	rb->constraints.freezeRotation.z = true;

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
	WindowManager::hierarchyWindow->treeList->Delete(gameobject->GetPath());
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

	//���O�̌�⌈��
	std::string newName = name;
	if (!isForce) {
		int no = 1;	//���h�~�p�ԍ�
		//���Ȃ��Ȃ�܂ŌJ��Ԃ�
		while (map.contains(newName)) {
			newName = name + " (" + std::to_string(no++) + ")";	//�V�������̖��O���쐬
		}
	}

	//TreeList�̖��O��ς���
	TreeNode* node = WindowManager::hierarchyWindow->treeList->GetRoot();	//���[�g�擾
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
	this->name = newName;	//���ۂɕς���
}

void Scene::PreparationLibrate()
{
	nowCamera = nullptr;
	cameras.clear();

	for (auto& gameobject : gameobjects) {
		//gameobject�̉������
		gameobject->PreparationLibrate();
		//���
		delete(gameobject);
		gameobject = nullptr;
	}
	gameobjects.clear();

	//sceneInfos����폜
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
