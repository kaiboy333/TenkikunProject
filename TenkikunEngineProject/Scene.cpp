#include "Scene.h"
#include "SceneManager.h"
#include "ImageRenderer.h"
#include "Animator.h"
#include "ProjectFileManager.h"
#include "Debug.h"

void Scene::Init()
{
	Window* window = WindowManager::hierarchyWindow;
	treeList = new TreeList(window->startX, window->startY, window->width, window->height, window, true, true, this->name);
	SetName("Scene", false);	//���O������(���͕ς���)
}

void Scene::Update()
{
	for (GameObject* gameobject : gameobjects) {
		gameobject->Update();	//�Q�[���I�u�W�F�N�g�̍X�V
		//for (Transform* child : gameobject->transform->children) {
		//	child->Update();
		//}
	}
}

void Scene::Draw(Window* parentWindow)
{
	Camera* camera = nowCamera;   //���݂̑Ώۂ�Camera��`��
	for (GameObject* gameobject : gameobjects) {
		gameobject->Draw(parentWindow, camera);	//�Q�[���I�u�W�F�N�g�̕`��
	}
}

GameObject* Scene::CreateEmpty()
{
	GameObject* gameobject = new GameObject();	//GameObject���쐬
	gameobject->transform = gameobject->AddComponent<Transform>();	//Transform������
	gameobjects.emplace_back(gameobject);	//���X�g�ɒǉ�
	gameobject->SetName("GameObject");	//���O�ύX(�����̖��O)
	treeList->Add(new TreeNode(gameobject->GetName(), treeList, treeList->isFirstOpen), treeList->GetRoot());	//TreeNode�ɂ��ǉ�
	return gameobject;
}

GameObject* Scene::CreateSquare()
{
	GameObject* gameobject = CreateEmpty();	//���GameObject���쐬
	gameobject->SetName("Square");	//���O�ύX

	ImageRenderer* imageRenderer = gameobject->AddComponent<ImageRenderer>();	//ImageRenderer�R���|�[�l���g�쐬
	Component* component = static_cast<Component*>(imageRenderer);
	//�l�p�̉摜��T��
	for (std::pair<std::string, std::filesystem::path> pair : ProjectFileManager::guidAndPath) {
		if (pair.second.string() == ProjectFileManager::resourceFilePath.string() + "\\Square.png") {
			imageRenderer->image = new Image(pair.second);	//image���Z�b�g
			break;
		}
	}
	return gameobject;
}

GameObject* Scene::CreateCamera() 
{
	GameObject* gameobject = CreateEmpty();	//���GameObject���쐬
	gameobject->SetName("MainCamera");	//���O�ύX

	Camera* camera = gameobject->AddComponent<Camera>();	//Camera�R���|�[�l���g�쐬
	SetNowCamera(camera);	//���݂̃J�����ɂ�����Z�b�g
	Scene* scene = SceneManager::GetNowScene();	//Scene���擾
	return gameobject;
}

GameObject* Scene::CreateTenkikun()
{
	GameObject* gameobject = CreateEmpty();	//���GameObject���쐬
	gameobject->SetName("Tenkikun");	//���O�ύX

	ImageRenderer* imageRenderer = gameobject->AddComponent<ImageRenderer>();	//ImageRenderer�R���|�[�l���g�쐬
	//Component* component = static_cast<Component*>(imageRenderer);
	//�V�C����̉摜��T��
	for (std::pair<std::string, std::filesystem::path> pair : ProjectFileManager::guidAndPath) {
		if (pair.second.string() == ProjectFileManager::resourceFilePath.string() + "\\Tenkikun.png") {
			imageRenderer->image = new Image(pair.second);	//image���Z�b�g
			break;
		}
	}
	return gameobject;
}

GameObject* Scene::CreateUnityChan()
{
	GameObject* gameobject = CreateEmpty();	//���GameObject���쐬
	gameobject->SetName("UnityChan");	//���O�ύX

	ImageRenderer* imageRenderer = gameobject->AddComponent<ImageRenderer>();	//ImageRenderer�R���|�[�l���g�쐬
	Animator* animator = gameobject->AddComponent<Animator>();	//Animator�R���|�[�l���g�쐬

	//�A�j���[�V�����R���g���[���[�̍쐬
	std::filesystem::path acPath = ProjectFileManager::currentPath.string() + "\\" + "PlayerAnimatorController" + ".animctr";
	AnimatorController* ac = static_cast<AnimatorController*>(ProjectFileManager::CreateInfo(acPath));

	animator->ac = ac;	//Animator��ac���Z�b�g
	ac->AddFloatParamater("isSpeed", 0.0f);	//�p�����[�^�[���Z�b�g
	//ac->animator = animator;	//ac��Animator���Z�b�g

	//�ҋ@�A�j���[�V�����̃Z�b�g
	//�ҋ@�A�j���[�V�����̍쐬
	std::filesystem::path idleAnimPath = ProjectFileManager::currentPath.string() + "\\" + "IdleAnimation" + ".anim";
	Animation* idleAnim = static_cast<Animation*>(ProjectFileManager::CreateInfo(idleAnimPath));

	//�ҋ@�摜�̍쐬
	std::vector<Image*> idleImages;
	for (int i = 0; i < 3; i++) {
		for (std::pair<std::string, std::filesystem::path> pair : ProjectFileManager::guidAndPath) {
			if (pair.second.string() == ProjectFileManager::resourceFilePath.string() + "\\UnityChan_Idle" + std::to_string(i) + ".png") {
				idleImages.push_back(new Image(pair.second));	//�摜�ǉ�
				break;
			}
		}
	}
	//�A�j���[�V�����L�[�Ƃ��Ēǉ�
	idleAnim->AddAnimationKey(idleImages, 10);
	//ac�ɃA�j���[�V�������Z�b�g����State���擾
	AnimationState* idleState = animator->AddState(idleAnim, "Idle");

	//����A�j���[�V�����̃Z�b�g
	//�ҋ@�A�j���[�V�����̍쐬
	std::filesystem::path runAnimPath = ProjectFileManager::currentPath.string() + "\\" + "RunAnimation" + ".anim";
	Animation* runAnim = static_cast<Animation*>(ProjectFileManager::CreateInfo(idleAnimPath));
	
	//����摜�̍쐬
	std::vector<Image*> runImages;
	for (int i = 0; i < 8; i++) {
		for (std::pair<std::string, std::filesystem::path> pair : ProjectFileManager::guidAndPath) {
			if (pair.second.string() == ProjectFileManager::resourceFilePath.string() + "\\UnityChan_Run" + std::to_string(i) + ".png") {
				runImages.push_back(new Image(pair.second));	//�摜�ǉ�
				break;
			}
		}
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
	treeList->Delete(gameobject->GetName());
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
	std::unordered_map<std::string, std::filesystem::path>& map = SceneManager::scenePathes;

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
			//�V�[���p�X�̃}�b�v�̖��O��ς���(�u������)
			map.insert_or_assign(map.find(this->name), name, map[this->name]);
		}
	}
	this->name = name;	//���ۂɕς���
}

//void Scene::DestroyGameObject(GameObject* gameobject)
//{
//	auto iter = std::find(gameobjects.begin(), gameobjects.end(), gameobject);
//}
