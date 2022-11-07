#include "RigidBody.h"
#include "Transform.h"
#include "GameObject.h"
#include "Time.h"
#include "Physics.h"

RigidBody::RigidBody(GameObject* gameobject) : Component(gameobject)
{
	solverBody = new SolverBody();
}

void RigidBody::Update()
{
	if (bodyType == BodyType::Dynamic) {
		//重力の更新
		AddForce(Vector3::Down() * mass * Physics::g * gravityScale);
	}

	if (constraints.freezePosition.x) {
		velocity.x = 0;
	}
	if (constraints.freezePosition.y) {
		velocity.y = 0;
	}
	if (constraints.freezeRotation.z) {
		angularVelocity.z = 0;
	}

	if (bodyType != BodyType::Static) {
		Transform* transform = gameobject->transform;
		//位置の更新
		transform->localPosition += velocity * Time::GetDeltaTime();
		//角度の更新
		transform->localRotation += angularVelocity * Time::GetDeltaTime();
	}
	else {
		velocity = Vector3::Zero();
		angularVelocity = Vector3::Zero();
	}
}

void RigidBody::AddForce(Vector3 force, ForceMode forceMode)
{
	switch (forceMode) {
		case ForceMode::Force:
			velocity += force * Time::GetDeltaTime() / mass;
			break;
		case ForceMode::Acceleration:
			velocity += force * Time::GetDeltaTime();
			break;
		case ForceMode::Impulse:
			velocity += force / mass;
			break;
		case ForceMode::VelocityChange:
			velocity += force;
			break;
	}
}

void RigidBody::PreparationLibrate()
{
	//自身の解放準備
	Component::PreparationLibrate();
}
