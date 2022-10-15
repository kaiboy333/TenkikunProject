#pragma once

#include "Component.h"

class RigidBody	: public Component
{
	public:
		enum class ForceMode {
			Force,
			Acceleration,
			Impulse,
			VelocityChange,
		};

		//���x
		Vector3 velocity;
		//�p���x
		Vector3 angularVelocity;
		//�d�͂̉��{��
		float gravityScale = 1.0f;
		//����
		float mass = 1.0f;

		RigidBody(GameObject* gameobject);

		virtual void Update() override;

		void AddForce(Vector3 force, ForceMode forceMode = ForceMode::Force);

		virtual void PreparationLibrate() override;

	private:
		//���v�̗�
		Vector3 force;
};

