#include "Camera.h"
#include "SceneManager.h"
#include "GameWindow.h"
#include "WindowManager.h"

Camera::Camera(GameObject* gameobject) : Component(gameobject)
{
	this->width = WindowManager::gameWindow->width;
	this->height = WindowManager::gameWindow->height;
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

	 return Vector3((screenPosition.x - parentWindow->width / 2.0f - parentWindow->startX) / camera->zoom + cameraPos.x , -(screenPosition.y - parentWindow->height / 2.0f - parentWindow->startY) / camera->zoom + cameraPos.y, screenPosition.z);
 }

 Vector3 Camera::WorldToScreenPoint(Vector3 worldPosition)
 {
	 Scene* scene = SceneManager::GetNowScene();
	 Camera* camera = scene->GetNowCamera();
	 GameWindow* parentWindow = WindowManager::gameWindow;
	 Vector3 cameraPos = camera->gameobject->transform->position;

	 return Vector3((worldPosition.x - cameraPos.x) * camera->zoom + parentWindow->width / 2.0f + parentWindow->startX, -(worldPosition.y - cameraPos.y) * camera->zoom + parentWindow->height / 2.0f + parentWindow->startY, worldPosition.z);
 }

 void Camera::PreparationLibrate()
 {
	 //©g‚Ì‰ğ•ú€”õ
	 Component::PreparationLibrate();
 }


