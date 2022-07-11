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
	for (Image* image : ProjectFileManager::GetSpecificInfos<Image>()) {
		if (image->GetPath().string() == ProjectFileManager::resourceFilePath.string() + "\\Square.png") {
			imageRenderer->image = image;	//image���Z�b�g
			break;
		}
	}
	return gameobject;
}

GameObject* Scene::CreateCamera() 
{
	GameObject* gameobject = CreateEmpty();	//���GameObject���쐬
	gameobject->SetName("Main Camera");	//���O�ύX

	Camera* camera = gameobject->AddComponent<Camera>();	//Camera�R���|�[�l���g�쐬
	SetNowCamera(camera);	//���݂̃J�����ɂ�����Z�b�g
	Scene* scene = SceneManager::GetNowScene();	//Scene���擾
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
			children->erase(std::remove(children->begin(), children->end(), transform));
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
