#include "Camera.h"
#include "SceneManager.h"
#include "GameWindow.h"
#include "WindowManager.h"

Camera::Camera(GameObject* gameobject) : Component(gameobject)
{
	this->width = 700;
	this->height = 500;
}

void Camera::Update()
{
	//zoom += Input::GetMouseWheelRoteValue() * zoomSpeed;
}

 Vector3 Camera::ScreenToWorldPoint(Vector3 screenPosition)
 {
	 GameWindow* gameWindow = WindowManager::gameWindow;

	 Scene* scene = SceneManager::GetNowScene();
	 Camera* camera = scene->GetNowCamera();
	 GameWindow* parentWindow = WindowManager::gameWindow;
	 Vector3 cameraPos = camera->gameobject->transform->position;

	 return Vector3(screenPosition.x / camera->zoom - parentWindow->width / 2.0f + cameraPos.x - parentWindow->startX, -(screenPosition.y / camera->zoom - parentWindow->height / 2.0f + cameraPos.y - parentWindow->startY), screenPosition.z);
 }

 Vector3 Camera::WorldToScreenPoint(Vector3 worldPosition)
 {
	 Scene* scene = SceneManager::GetNowScene();
	 Camera* camera = scene->GetNowCamera();
	 GameWindow* parentWindow = WindowManager::gameWindow;
	 Vector3 cameraPos = camera->gameobject->transform->position;

	 return Vector3((worldPosition.x + parentWindow->width / 2.0f - cameraPos.x + parentWindow->startX) * camera->zoom, -(worldPosition.y + parentWindow->height / 2.0f - cameraPos.y + parentWindow->startY) * camera->zoom, worldPosition.z);
 }


