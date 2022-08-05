#include "ImageRenderer.h"
#include "DxLib.h"
#include "Transform.h"
#include "GameObject.h"
#include "WindowManager.h"

ImageRenderer::ImageRenderer(GameObject* gameobject) : DrawComponent(gameobject)
{
}

void ImageRenderer::Update()
{

}

void ImageRenderer::Draw()
{
	if (image != nullptr) {
		if (image->GetGH() != -1) {
			Vector3 drawPos = GetDrawPos(gameobject->transform->position);
			GameWindow* gameWindow = WindowManager::gameWindow;
			Vector3 scale = this->gameobject->transform->scale;
			Vector3 rota = this->gameobject->transform->rotation;

			SetDrawBlendMode(DX_BLENDMODE_ALPHA, image->GetAlpha());

			DrawRotaGraph3F(drawPos.x, drawPos.y, image->GetWidth() / 2, image->GetHeight() / 2, scale.x, scale.y, -MyMath::EulerToRad(rota.z), image->GetGH(), true, isFlipX, isFlipY);	//•`‰æ
		}
	}
}