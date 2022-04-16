#pragma once

#include "Component.h"
#include "Vector3.h"
#include <vector>

class Transform : public Component
{
	public:
		Vector3 position;	//�ʒu
		Vector3 rotation;	//��]�p�x(�I�C���[�p)
		Vector3 scale = Vector3(1, 1, 1);		//�傫��

		Vector3 localPosition;
		Vector3 localRotation;
		Vector3 localScale = Vector3(1, 1, 1);

		Transform* parent;	//�e��Transform

		void Update();	//�e�̑��΂ɂ���ĕς���

	private:
		std::vector<Transform*> childrens;	//�q��Transform����
};

