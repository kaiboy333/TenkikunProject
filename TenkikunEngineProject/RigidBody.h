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

		//ë¨ìx
		Vector3 velocity;
		//èdóÕÇÃâΩî{Ç©
		float gravityScale = 1.0f;
		//éøó 
		float mass = 1.0f;

		RigidBody(GameObject* gameobject);

		virtual void Update() override;

		void AddForce(Vector3 force, ForceMode forceMode = ForceMode::Force);

	private:
		//çáåvÇÃóÕ
		Vector3 force;
};

