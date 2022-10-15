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
	if (isHit) {
		downColor = GetColor(255, 0, 0);
	}
	else {
		downColor = GetColor(0, 255, 0);
	}

	Vector3 drawPos = GetDrawPos(GetPosition());
	GameWindow* gameWindow = WindowManager::gameWindow;
	float zoom = SceneManager::GetNowScene()->GetNowCamera()->zoom;

	DrawOvalAA(drawPos.x, drawPos.y, GetActualRadious() * zoom, GetActualRadious() * zoom, 30, downColor, FALSE);

	//交点の描画
	Collider::Draw();
}

float CircleCollider::GetActualRadious()
{
	//大きさ取得
	Vector3 scale = this->gameobject->transform->scale;
	//x、yの大きいほうを取得
	float maxScale = std::max<float>(scale.x, scale.y);
	
	return radious * maxScale;
}
