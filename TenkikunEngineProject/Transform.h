#pragma once

#include <vector>
#include "Vector3.h"
#include "Component.h"
#include "Matrix.h"
#include "Property.h"

class Transform : public Component
{
	public:
		//���[���h���
		//�ʒu
		Property<Vector3> position{
			position_t
				, [this](Vector3 v) {
					ChangedWorldPos(v);
				}
				, nullptr
		};
		//��]
		Property<Vector3> rotation{
			rotation_t
				, [this](Vector3 v) {
					//360�x��������0�ɂȂ�悤�ɂ���
					v.x = fmodf(v.x, 360);
					v.y = fmodf(v.y, 360);
					v.z = fmodf(v.z, 360);
					ChangedWorldRote(v);
				}
				, nullptr
		};
		//�傫��
		Property<Vector3> scale{
			scale_t
				, [this](Vector3 v) {
					ChangedWorldScale(v);
				}
				, nullptr
		};


		//���[�J�����
		//�ʒu
		Property<Vector3> localPosition{
			localPosition_t
				, [this](Vector3 v) {
					ChangedLocalPos(v);
				}
				, nullptr
		};
		//��]
		Property<Vector3> localRotation{
			localRotation_t
				, [this](Vector3 v) {
					//360�x��������0�ɂȂ�悤�ɂ���
					v.x = fmodf(v.x, 360);
					v.y = fmodf(v.y, 360);
					v.z = fmodf(v.z, 360);
					ChangedLocalRote(v);
				}
				, nullptr
		};
		//�傫��
		Property<Vector3> localScale{
			localScale_t
				, [this](Vector3 v) {
					ChangedLocalScale(v);
				}
				, nullptr
		};

		Transform* parent = nullptr;	//�e��Transform

		Transform();

		void Update() override;	//�e�̑��΂ɂ���ĕς���

		void SetParent(Transform* newParent);	//�e�I�u�W�F�N�g���Z�b�g����

		std::vector<Transform*> children;	//�q��Transform����

	private:
		Vector3 position_t;
		Vector3 rotation_t;
		Vector3 scale_t = Vector3::One();

		Vector3 localPosition_t;
		Vector3 localRotation_t;
		Vector3 localScale_t = Vector3::One();

		void ChangedWorldPos(Vector3 pos);	//���[���h�ʒu���ύX���ꂽ��Ăяo��
		void ChangedLocalPos(Vector3 localPos);	//���[�J���ʒu���ύX���ꂽ��Ăяo��

		void ChangedWorldRote(Vector3 rote);	//��]���ύX���ꂽ��Ăяo��
		void ChangedLocalRote(Vector3 localRote);	//��]���ύX���ꂽ��Ăяo��

		void ChangedWorldScale(Vector3 scale);	//�傫�����ύX���ꂽ��Ăяo��
		void ChangedLocalScale(Vector3 localScale);	//�傫�����ύX���ꂽ��Ăяo��

};
