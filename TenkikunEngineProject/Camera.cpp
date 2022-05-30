#include "Camera.h"
#include "SceneManager.h"
#include "GameWindow.h"
#include "WindowManager.h"

Camera::Camera()
{
	this->width = 700;
	this->height = 500;
	Scene* scene = SceneManager::GetNowScene();
	scene->cameras.emplace_back(this);	//Scene‚É‚ ‚éCameraƒŠƒXƒg‚ÉŽ©g‚ð’Ç‰Á
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

	 return Vector3(screenPosition.x / camera->zoom - window->width / 2.0f + cameraPos.x, screenPosition.y / camera->zoom - window->height / 2.0f + cameraPos.y, screenPosition.z);
 }

 Vector3 Camera::WorldToScreenPoint(Vector3 worldPosition)
 {
	 Scene* scene = SceneManager::GetNowScene();
	 Camera* camera = scene->GetNowCamera();
	 GameWindow* window = WindowManager::gameWindow;
	 Vector3 cameraPos = camera->gameobject->transform->position;

	 return Vector3((worldPosition.x + window->width / 2.0f - cameraPos.x) * camera->zoom, (worldPosition.y + window->height / 2.0f - cameraPos.y) * camera->zoom, worldPosition.z);
 }


