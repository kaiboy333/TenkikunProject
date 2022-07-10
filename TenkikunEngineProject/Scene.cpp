#include "Scene.h"
#include "SceneManager.h"
#include "ImageRenderer.h"
#include "Animator.h"
#include "ProjectFileManager.h"
#include <unordered_map>

Scene::Scene()
{

}

void Scene::Init()
{
	Window* window = WindowManager::hierarchyWindow;
	treeList = new TreeList(window->startX, window->startY, window->width, window->height, window, true, true, this->name);
	SetName("Scene");	//���O������
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
	Camera* camera = cameras[this->drawCameraNo];   //���݂̑Ώۂ�Camera��`��
	for (GameObject* gameobject : gameobjects) {
		gameobject->Draw(parentWindow, camera);	//�Q�[���I�u�W�F�N�g�̕`��
	}
}

GameObject* Scene::CreateEmpty()
{
	GameObject* gameobject = new GameObject();	//GameObject���쐬
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
	std::string currentPath = "image/square.png";	//�摜�̃p�X
	Image* image = new Image(currentPath);		//�摜��ǂݍ���
	imageRenderer->image = image;	//image���Z�b�g
	return gameobject;
}

GameObject* Scene::CreateCamera() 
{
	GameObject* gameobject = CreateEmpty();	//���GameObject���쐬
	gameobject->SetName("Main Camera");	//���O�ύX

	Camera* camera = gameobject->AddComponent<Camera>();	//Camera�R���|�[�l���g�쐬
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

Camera* Scene::GetNowCamera()
{
	return cameras[drawCameraNo];
}

std::string Scene::GetName()
{
	return name;
}

void Scene::SetName(std::string name)
{
	int no = 1;	//���h�~�p�ԍ�
	//�V�[���p�X�̃}�b�v���擾
	std::unordered_map<std::string, std::filesystem::path>& map = SceneManager::scenePathes;
	//���Ȃ��Ȃ�܂ŌJ��Ԃ�
	while (map.contains(name)) {
		name = name + " (" + std::to_string(no++) + ")";	//�V�������̖��O���쐬
	}
	//TreeList�̖��O��ς���
	TreeList* treeList = SceneManager::GetNowScene()->treeList;
	TreeNode* node = treeList->GetRoot();	//���[�g�m�[�h�擾
	if (node) {
		//���O�Z�b�g
		node->SetElement(name);
	}
	//�V�[���p�X�̃}�b�v�̖��O��ς���(�u������)
	map.insert_or_assign(map.find(this->name), name, map[this->name]);
	this->name = name;	//���ۂɕς���
}

//void Scene::DestroyGameObject(GameObject* gameobject)
//{
//	auto iter = std::find(gameobjects.begin(), gameobjects.end(), gameobject);
//}
