#pragma once

#include "Component.h"
#include "Physics.h"

class RigidBody	: public Component
{
	public:
		enum class ForceMode {
			Force,
			Acceleration,
			Impulse,
			VelocityChange,
		};

		enum class BodyType {
			Dynamic,
			Static,
		};
		BodyType bodyType = BodyType::Dynamic;

		//���x
		Vector3 velocity;
		//�p���x
		Vector3 angularVelocity;
		//�d�͂̉��{��
		float gravityScale = 1.0f;
		//����
		float mass = 1.0f;
		//�����W��
		float restritution = 0.5f;
		//���C�W��
		float friction = 0.5f;
		//�S���p�̒l
		SolverBody* solverBody = nullptr;


		struct FreezePosition {
			bool x = false;
			bool y = false;
		};
		struct FreezeRotation {
			bool z = false;
		};
		//����
		struct Constraints {
			FreezePosition freezePosition;
			FreezeRotation freezeRotation;
		};
		Constraints constraints;

		RigidBody(GameObject* gameobject);

		virtual void Update() override;

		void AddForce(Vector3 force, ForceMode forceMode = ForceMode::Force);

		virtual void PreparationLibrate() override;
};

