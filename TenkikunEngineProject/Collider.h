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

		bool isHit = false;

		unsigned int downColor = GetColor(0, 255, 0);

		Collider(GameObject* gameobject);

		virtual void Update() override;

		virtual void Draw() override;

		//�R���C�_�[�̒��S�_��Ԃ�
		Vector3 GetPosition() const;

		virtual Rect GetBoundingBox() const = 0;	//�o�E���f�B���O�{�b�N�X��Ԃ�

		void DrawBoundingBox() const;	//�o�E���f�B���O�{�b�N�X�̕`��

		virtual float GetI() const = 0;	//�������[�����g���擾

		int GetNo() const;	//�ԍ��擾

		bool operator==(const Collider& other) const;
		bool operator!=(const Collider& other) const;
		bool operator<(const Collider& other) const;
		bool operator>(const Collider& other) const;

	private:
		int no = 0;
		static int newNo;
};
