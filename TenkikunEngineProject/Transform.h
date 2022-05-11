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

		std::vector<Transform*> children;	//�q��Transform����

	private:
		//�O��̃��[���h
		Vector3 beforePosition;	//�ʒu
		Vector3 beforeRotation;	//��]�p�x(�I�C���[�p)
		Vector3 beforeScale = Vector3::One();	//�傫��

		//�O��̃��[�J��
		Vector3 beforeLocalPosition;
		Vector3 beforeLocalRotation;
		Vector3 beforeLocalScale = Vector3::One();

		//��������(���[���h�ƃ��[�J�����킹��)
		Vector3 deltaPosition;
		Vector3 deltaRotation;
		Vector3 deltaScale;

		void RivisionUpdate();	//���[�J���ƃ��[���h�ł��ꂽ�����C������

		void TransUpdate();	//�e�̃��[���h���W�ƍ��̃��[�J�����W�ō��̃��[���h���W�����߂�
		void RotateUpdate();	//�e�̃��[���h��]�ƍ��̃��[�J����]�ō��̃��[���h��]�����߂�
		void ScaleUpdate();	//�e�̃��[���h�k�ڂƍ��̃��[�J���k�ڂō��̃��[���h�k�ڂ����߂�
};
