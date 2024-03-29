#include "CircleCollider.h"
#include <cmath>
#include "RigidBody.h"

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

	//円を描画
	DrawOvalAA(drawPos.x, drawPos.y, GetActualRadious() * zoom, GetActualRadious() * zoom, 30, downColor, FALSE);

	//交点の描画
	Collider::Draw();
}

float CircleCollider::GetActualRadious() const
{
	//大きさ取得
	Vector3 scale = this->gameobject->transform->scale;
	//x、yの大きいほうを取得
	float maxScale = std::max<float>(scale.x, scale.y);
	
	return radious * maxScale;
}

Rect CircleCollider::GetBoundingBox() const
{
	auto actualRadious = GetActualRadious();
	Vector3 centerPos = gameobject->transform->position;

	Vector3 leftDownPos = centerPos - Vector3(1, 1, 0) * actualRadious;

	return Rect(leftDownPos.x, leftDownPos.y, 2 * actualRadious, 2 * actualRadious);
}

float CircleCollider::GetI() const
{
	auto rb = gameobject->GetComponent<RigidBody>();

	return rb ? (rb->mass * std::powf(GetActualRadious(), 2)) / 2 : FLT_MAX;
}
