#include "CircleCollider.h"
#include <cmath>

CircleCollider::CircleCollider(GameObject* gameobject) : Collider(gameobject)
{
	//ImageRenderer取得
	ImageRenderer* ir = gameobject->GetComponent<ImageRenderer>();

	if (ir) {
		//Imageがあるなら
		if (ir->image) {
			//Imageの幅と高さの大きいほうの半分を半径に設定
			radious = std::max<float>(ir->image->GetWidth(), ir->image->GetHeight()) / 2;
		}
	}
}

void CircleCollider::Draw()
{
	Vector3 drawPos = GetDrawPos(GetPosition());
	GameWindow* gameWindow = WindowManager::gameWindow;
	Vector3 scale = this->gameobject->transform->scale;
	float maxScale = std::max<float>(scale.x, scale.y);

	DrawOvalAA(drawPos.x, drawPos.y, radious * maxScale, radious * maxScale, 30, color, FALSE);
}