#pragma once

#include <vector>
#include "Vector3.h"
#include "Component.h"
#include "Matrix.h"

class Transform : public Component
{
	public:
		Vector3 position;	//�ʒu
		Vector3 rotation;	//��]�p�x(�I�C���[�p)
		Vector3 scale = Vector3::One();		//�傫��

		Vector3 localPosition;
		Vector3 localRotation;
		Vector3 localScale = Vector3::One();

		Transform* parent = nullptr;	//�e��Transform

		Transform();

		void Update() override;	//�e�̑��΂ɂ���ĕς���

		void SetParent(Transform* newParent);	//�e�I�u�W�F�N�g���Z�b�g����

	private:
		std::vector<Transform*> children;	//�q��Transform����

		Vector3 GetLocalToWorldPos();	//�e�̃��[���h���W�ƍ��̃��[�J�����W�ō��̃��[���h���W�����߂�
		Vector3 GetLocalToWorldRote();	//�e�̃��[���h��]�ƍ��̃��[�J����]�ō��̃��[���h��]�����߂�
		Vector3 GetLocalToWorldScale();	//�e�̃��[���h�k�ڂƍ��̃��[�J���k�ڂō��̃��[���h�k�ڂ����߂�
};
