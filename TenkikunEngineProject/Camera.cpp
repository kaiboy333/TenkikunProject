#include "Camera.h"
#include "SceneManager.h"
#include "GameWindow.h"
#include "WindowManager.h"

Camera::Camera()
{
	this->width = 700;
	this->height = 500;
	Scene* scene = SceneManager::GetNowScene();
	scene->cameras.emplace_back(this);	//SceneにあるCameraリストに自身を追加
}

void Camera::Update()
{
}

 Vector3 Camera::ScreenToWorldPoint(Vector3 screenPosition)
 {
	 GameWindow* gameWindow = WindowManager::gameWindow;

	 Scene* scene = SceneManager::GetNowScene();
	 Camera* camera = scene->GetNowCamera();
	 GameWindow* window = WindowManager::gameWindow;
	 Vector3 cameraPos = camera->gameobject->transform->position;

	 return Vector3(screenPosition.x / camera->zoom - window->width / 2.0f + cameraPos.x - window->startX, screenPosition.y / camera->zoom - window->height / 2.0f + cameraPos.y - window->startY, screenPosition.z);
 }

 Vector3 Camera::WorldToScreenPoint(Vector3 worldPosition)
 {
	 Scene* scene = SceneManager::GetNowScene();
	 Camera* camera = scene->GetNowCamera();
	 GameWindow* window = WindowManager::gameWindow;
	 Vector3 cameraPos = camera->gameobject->transform->position;

	 return Vector3((worldPosition.x + window->width / 2.0f - cameraPos.x + window->startX) * camera->zoom, (worldPosition.y + window->height / 2.0f - cameraPos.y + window->startY) * camera->zoom, worldPosition.z);
 }


