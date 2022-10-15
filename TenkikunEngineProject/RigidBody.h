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

		//速度
		Vector3 velocity;
		//角速度
		Vector3 angularVelocity;
		//重力の何倍か
		float gravityScale = 1.0f;
		//質量
		float mass = 1.0f;

		RigidBody(GameObject* gameobject);

		virtual void Update() override;

		void AddForce(Vector3 force, ForceMode forceMode = ForceMode::Force);

		virtual void PreparationLibrate() override;

	private:
		//合計の力
		Vector3 force;
};

