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
	Vector3 drawPos = GetDrawPos(GetPosition());
	GameWindow* gameWindow = WindowManager::gameWindow;
	Vector3 scale = this->gameobject->transform->scale;
	float maxScale = std::max<float>(scale.x, scale.y);
	float zoom = SceneManager::GetNowScene()->GetNowCamera()->zoom;

	DrawOvalAA(drawPos.x, drawPos.y, radious * maxScale * zoom, radious * maxScale * zoom, 30, color, FALSE);

	//��_�̕`��
	Collider::Draw();
}