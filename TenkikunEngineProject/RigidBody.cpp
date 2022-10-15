#include "RigidBody.h"
#include "Transform.h"
#include "GameObject.h"
#include "Time.h"
#include "Physics.h"

RigidBody::RigidBody(GameObject* gameobject) : Component(gameobject)
{

}

void RigidBody::Update()
{
	//�d�͂̍X�V
	AddForce(Vector3::Down() * mass * Physics::g * gravityScale);

	Transform* transform = gameobject->transform;
	//�ʒu�̍X�V
	transform->localPosition += velocity * Time::GetDeltaTime();
	//�p�x�̍X�V
	transform->localRotation += angularVelocity * Time::GetDeltaTime();
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
	//���g�̉������
	Component::PreparationLibrate();
}
