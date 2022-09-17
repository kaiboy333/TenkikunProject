#pragma once

#include "DrawComponent.h"
#include "Vector3.h"
#include "DxLib.h"
#include <vector>
#include "MyMath.h"
#include "Matrix.h"
#include "GameObject.h"

class Collider : public DrawComponent
{
	public:
		Vector3 offset;	//���S����ǂ̂��炢����Ă��邩

		bool isTrigger = false;	//���蔲���邩

		unsigned int color = GetColor(0, 255, 0);

		std::vector<Vector3> crossPoints;

		Collider(GameObject* gameobject);

		virtual void Update() override;

		virtual void Draw() override;

		//�R���C�_�[�̒��S�_��Ԃ�
		Vector3 GetPosition();
};
