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

		//ë¨ìx
		Vector3 velocity;
		//äpë¨ìx
		Vector3 angularVelocity;
		//èdóÕÇÃâΩî{Ç©
		float gravityScale = 1.0f;
		//éøó 
		float mass = 1.0f;
		//îΩî≠åWêî
		float restritution = 0.5f;
		//ñÄéCåWêî
		float friction = 0.5f;
		//çSë©ópÇÃíl
		SolverBody* solverBody = nullptr;


		struct FreezePosition {
			bool x = false;
			bool y = false;
		};
		struct FreezeRotation {
			bool z = false;
		};
		//êßå¿
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

