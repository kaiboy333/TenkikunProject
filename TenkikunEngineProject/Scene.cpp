#include "Scene.h"
#include "SceneManager.h"
#include "ImageRenderer.h"
#include "Animator.h"

void Scene::Init()
{
	CreateCamera();	//�J��������

	CreateSquare();	//�l�p���摜�𐶐�
	GameObject* s2 = CreateSquare();	//�l�p���摜�𐶐�
	s2->name = "Square2";
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

void Scene::Draw(Window* window)
{
	Camera* camera = cameras[this->drawCameraNo];   //���݂̑Ώۂ�Camera��`��
	for (GameObject* gameobject : gameobjects) {
		gameobject->Draw(window, camera);	//�Q�[���I�u�W�F�N�g�̕`��
	}
}

GameObject* Scene::CreateEmpty()
{
	GameObject* gameobject = new GameObject();	//GameObject���쐬
	gameobjects.emplace_back(gameobject);	//���X�g�ɒǉ�
	return gameobject;
}

GameObject* Scene::CreateSquare()
{
	GameObject* gameobject = CreateEmpty();	//���GameObject���쐬
	gameobject->name = "Square";	//���O�ύX

	ImageRenderer* imageRenderer = gameobject->AddComponent<ImageRenderer>();	//ImageRenderer�R���|�[�l���g�쐬
	std::string path = "image/square.png";	//�摜�̃p�X
	Image* image = new Image(path);		//�摜��ǂݍ���
	imageRenderer->image = image;	//image���Z�b�g
	return gameobject;
}

GameObject* Scene::CreateCamera() 
{
	GameObject* gameobject = CreateEmpty();	//���GameObject���쐬
	gameobject->name = "Main Camera";	//���O�ύX

	Camera* camera = gameobject->AddComponent<Camera>();	//Camera�R���|�[�l���g�쐬
	Scene* scene = SceneManager::GetNowScene();	//Scene���擾
	return gameobject;
}

void Scene::RemoveGameObject(GameObject* gameobject)
{
	gameobjects.erase(std::remove(gameobjects.begin(), gameobjects.end(), gameobject));
}

Camera* Scene::GetNowCamera()
{
	return cameras[drawCameraNo];
}

//void Scene::DestroyGameObject(GameObject* gameobject)
//{
//	auto iter = std::find(gameobjects.begin(), gameobjects.end(), gameobject);
//}
