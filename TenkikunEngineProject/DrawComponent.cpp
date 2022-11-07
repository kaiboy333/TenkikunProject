#include "DrawComponent.h"
#include "WindowManager.h"

DrawComponent::DrawComponent(GameObject* gameobject) : Component(gameobject)
{
}

void DrawComponent::Update()
{
}

void DrawComponent::Draw()
{

}

Vector3 DrawComponent::GetDrawPos(Vector3 pos)
{
	GameWindow* gameWindow = WindowManager::gameWindow;
	Camera* camera = SceneManager::GetNowScene()->GetNowCamera();

	float startDrawX = 0, startDrawY = 0;
	float drawWidth = (float)camera->width;
	float drawHeight = (float)camera->height;

	//Window‚Ì•û‚ªƒJƒƒ‰‚Ì•`‰æ”ÍˆÍ‚æ‚è‘å‚«‚¢‚È‚ç
	if (camera->width < gameWindow->width) {
		startDrawX = (gameWindow->width - camera->width) / 2.0f;
		//drawWidth = (float)camera->width;
	}
	if (camera->height < gameWindow->height) {
		startDrawY = (gameWindow->height - camera->height) / 2.0f;
		//drawHeight = (float)camera->height;
	}

	Vector3 cameraPos = camera->gameobject->transform->position;

	float drawX = (pos.x - cameraPos.x) * camera->zoom + startDrawX + gameWindow->width / 2.0f;
	float drawY = -(pos.y - cameraPos.y) * camera->zoom + startDrawY + gameWindow->height / 2.0f;

	return Vector3(gameWindow->startX + drawX, gameWindow->startY + drawY, 0);
}

void DrawComponent::PreparationLibrate()
{
	Component::PreparationLibrate();
}
