#include "CircleCollider.h"
#include <cmath>

CircleCollider::CircleCollider(GameObject* gameobject) : Collider(gameobject)
{
	//ImageRenderer�擾
	ImageRenderer* ir = gameobject->GetComponent<ImageRenderer>();

	if (ir) {
		//Image������Ȃ�
		if (ir->image) {
			//Image�̕��ƍ����̑傫���ق��̔����𔼌a�ɐݒ�
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

	//��_�̕`��
	Collider::Draw();
}

float CircleCollider::GetActualRadious()
{
	//�傫���擾
	Vector3 scale = this->gameobject->transform->scale;
	//x�Ay�̑傫���ق����擾
	float maxScale = std::max<float>(scale.x, scale.y);
	
	return radious * maxScale;
}
