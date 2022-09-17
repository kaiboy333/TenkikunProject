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
		//�d�͂̉��{��
		float gravityScale = 1.0f;
		//����
		float mass = 1.0f;

		RigidBody(GameObject* gameobject);

		virtual void Update() override;

		void AddForce(Vector3 force, ForceMode forceMode = ForceMode::Force);

	private:
		//���v�̗�
		Vector3 force;
};
