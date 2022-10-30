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
			Static,
			Dynamic,
		};
		BodyType bodyType = BodyType::Dynamic;

		//‘¬“x
		Vector3 velocity;
		//Šp‘¬“x
		Vector3 angularVelocity;
		//d—Í‚Ì‰½”{‚©
		float gravityScale = 1.0f;
		//¿—Ê
		float mass = 1.0f;
		//”½”­ŒW”
		float restritution = 0.5f;
		//–€CŒW”
		float friction = 0.5f;
		//S‘©—p‚Ì’l
		SolverBody* solverBody = nullptr;

		RigidBody(GameObject* gameobject);

		virtual void Update() override;

		void AddForce(Vector3 force, ForceMode forceMode = ForceMode::Force);

		virtual void PreparationLibrate() override;

	private:
		//‡Œv‚Ì—Í
		Vector3 force;
};

