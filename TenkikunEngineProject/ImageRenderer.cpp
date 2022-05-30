#include "ImageRenderer.h"
#include "DxLib.h"
#include "Transform.h"
#include "GameObject.h"
#include "WindowManager.h"

void ImageRenderer::Update()
{

}

void ImageRenderer::Draw(Window* window, Camera* camera)
{
	if (image != nullptr) {
		if (image->GetGH() != nullptr) {
			float startDrawX = 0, startDrawY = 0;
			float drawWidth = (float)camera->width;
			float drawHeight = (float)camera->height;

			//Windowの方がカメラの描画範囲より大きいなら
			if (camera->width < window->width) {
				startDrawX = (window->width - camera->width) / 2.0f;
				//drawWidth = (float)camera->width;
			}
			if (camera->height < window->height) {
				startDrawY = (window->height - camera->height) / 2.0f;
				//drawHeight = (float)camera->height;
			}

			GameWindow* gameWindow = WindowManager::gameWindow;

			////描画範囲制限
			//SetDrawArea(gameWindow->startX, gameWindow->startY, gameWindow->startX + gameWindow->width, gameWindow->startY + gameWindow->height);

			Vector3 pos = this->gameobject->transform->position;
			Vector3 scale = this->gameobject->transform->scale;
			Vector3 rota = this->gameobject->transform->rotation;

			float drawX = pos.x + startDrawX + window->width / 2.0f;
			float drawY = pos.y + startDrawY + window->height / 2.0f;

			////カメラによって動くのなら
			//if (this->isCameraAffected) {
				Vector3 cameraPos = camera->gameobject->transform->position;

				drawX = (drawX - cameraPos.x) * camera->zoom;
				drawY = (drawY - cameraPos.y) * camera->zoom;
			//}

			DrawRotaGraph3F(gameWindow->startX + drawX, gameWindow->startY + drawY, image->GetWidth() / 2, image->GetHeight() / 2, scale.x, scale.y, MyMath::EulerToRad(rota.z), *image->GetGH(), true, isFlipX, isFlipY);	//描画
		}
	}
}