#include "Camera.h"
#include "SceneManager.h"

Camera::Camera()
{
	this->width = 700;
	this->height = 500;
	Scene* scene = SceneManager::GetNowScene();
	scene->cameras.emplace_back(this);	//Scene�ɂ���Camera���X�g�Ɏ��g��ǉ�
}

void Camera::Update()
{
}

 void Camera::Draw(Window* window)
 {
	 Scene* scene = SceneManager::GetNowScene();
	 for (GameObject* gameobject : scene->gameobjects) {
		 gameobject->Draw(window, this);
		 //for (Transform* child : gameobject->transform->children) {
			// child->gameobject->Draw(window, this);
		 //}
	 }
 }
