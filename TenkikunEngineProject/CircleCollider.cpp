#include "CircleCollider.h"
#include <cmath>

CircleCollider::CircleCollider(GameObject* gameobject) : Collider(gameobject)
{
	//ImageRendereræ“¾
	ImageRenderer* ir = gameobject->GetComponent<ImageRenderer>();

	if (ir) {
		//Image‚ª‚ ‚é‚È‚ç
		if (ir->image) {
			//Image‚Ì•‚Æ‚‚³‚Ì‘å‚«‚¢‚Ù‚¤‚Ì”¼•ª‚ğ”¼Œa‚Éİ’è
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

	//Œğ“_‚Ì•`‰æ
	Collider::Draw();
}

float CircleCollider::GetActualRadious()
{
	//‘å‚«‚³æ“¾
	Vector3 scale = this->gameobject->transform->scale;
	//xAy‚Ì‘å‚«‚¢‚Ù‚¤‚ğæ“¾
	float maxScale = std::max<float>(scale.x, scale.y);
	
	return radious * maxScale;
}
