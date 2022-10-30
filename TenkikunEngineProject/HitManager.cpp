#include "HitManager.h"
#include "Collider.h"
#include "GJK.h"
#include "AABBTree.h"
#include "Time.h"
#include "Debug.h"
#include "EPA.h"
#include "RigidBody.h"
#include "Physics.h"

void HitManager::HitCheck()
{
	std::vector<Collider*> colliders;

	for (GameObject* gameobject : SceneManager::GetNowScene()->gameobjects) {
		std::vector<Collider*> objectColliders = gameobject->GetComponents<Collider>();	//�R���C�_�[�������擾
		colliders.insert(colliders.end(), objectColliders.begin(), objectColliders.end());	//���X�g�Ɉ�C�ɒǉ�
	}

	LARGE_INTEGER beforeTime;
	LARGE_INTEGER nowTime;

	//�J�n�������L�^
	QueryPerformanceCounter(&beforeTime);

	if (colliders.size() >= 2) {
		//�o�E���f�B���O�{�b�N�X���g�����Փ˔���
		auto hitPairColliders = BlodePhase(colliders);

		//���ۂ̌`��ł̏Փ˔���
		auto supportInfos = NarrawPhase(hitPairColliders);

		Response(supportInfos);
	}

	// ���̎��Ԃ��擾
	QueryPerformanceCounter(&nowTime);
	// (���̎��� - �O�t���[���̎���) / ���g�� = �o�ߎ���(�b�P��)
	double frameTime = static_cast<double>(nowTime.QuadPart - beforeTime.QuadPart) / static_cast<double>(Time::timeFreq.QuadPart);

	Debug::Log(std::to_string(frameTime));
}

std::vector<std::pair<Collider*, Collider*>> HitManager::BlodePhase(std::vector<Collider*>& colliders)
{
	std::vector<std::pair<Collider*, Collider*>> pairs;

	if (blodeMode == BlodeMode::AABB_TREE) {
		return AABBTree::GetHitPairColliders(colliders);
	}
	else if (blodeMode == BlodeMode::NONE) {

		for (auto& collider1 : colliders) {
			for (auto& collider2 : colliders) {
				pairs.push_back(std::make_pair(collider1, collider2));
			}
		}
	}

	return pairs;
}

std::vector<SupportInfo*> HitManager::NarrawPhase(std::vector<std::pair<Collider*, Collider*>>& hitPairColliders)
{
	std::vector<SupportInfo*> supportInfos;

	for (auto& hitPairCollider : hitPairColliders) {
		//�S�������R���C�_�[�Ȃ��΂�
		if (hitPairCollider.first == hitPairCollider.second)
			continue;
		//�����Q�[���I�u�W�F�N�g�̃R���C�_�[�Ȃ��΂�
		if (hitPairCollider.first->gameobject == hitPairCollider.second->gameobject)
			continue;

		auto supportInfo = GJK::IsHit(hitPairCollider.first, hitPairCollider.second);
		if (supportInfo) {
			hitPairCollider.first->isHit = true;
			hitPairCollider.second->isHit = true;
			supportInfos.push_back(supportInfo);
		}
	}

	return supportInfos;
}

void HitManager::Response(std::vector<SupportInfo*>& supportInfos) {
	timeStep = Time::GetDeltaTime();

	std::vector<HitInfo*> hitInfos;

	for (auto supportInfo : supportInfos) {
		auto hitInfo = EPA::GetHitInfo(supportInfo);
		//�Փˉ������s���Ȃ�
		if (hitInfo) {
			//���X�g�ɒǉ�
			hitInfos.push_back(hitInfo);
		}
	}

	//�\���o�[�p�v���L�V���쐬
	for (auto hitInfo : hitInfos) {
		std::vector<RigidBody*> rigidBodies = { hitInfo->c1->gameobject->GetComponent<RigidBody>(), hitInfo->c2->gameobject->GetComponent<RigidBody>() };
		std::vector<SolverBody*> solverBodies = {&rigidBodies[0]->solverBody, &rigidBodies[1]->solverBody};
		std::vector<Collider*> colliders = {hitInfo->c1, hitInfo->c2};

		for (int i = 0, len = (int)rigidBodies.size(); i < len; i++) {
			//�\���o�[�{�f�B�Ƀp�����[�^���Z�b�g
			if (rigidBodies[i]) {
				solverBodies[i]->massInv = 1 / rigidBodies[i]->mass;
				solverBodies[i]->inertiaInv = 1 / colliders[i]->GetI();
			}
			else {
				solverBodies[i]->massInv = 0;
				solverBodies[i]->inertiaInv = 0;
			}
		}
	}

	//�S���̃Z�b�g�A�b�v
	for (auto hitInfo : hitInfos) {
		RigidBody* bodyA = hitInfo->c1->gameobject->GetComponent<RigidBody>();
		SolverBody& solverBodyA = bodyA->solverBody;

		RigidBody* bodyB = hitInfo->c2->gameobject->GetComponent<RigidBody>();
		SolverBody& solverBodyB = bodyB->solverBody;
		for (auto& contactPoint : hitInfo->contact.contactPoints) {
			auto cpA = contactPoint.pointA;
			auto cpB = contactPoint.pointB;

			auto r1 = cpA - bodyA->gameobject->transform->position;
			auto r2 = cpB - bodyB->gameobject->transform->position;

			//��������Փ˖@����3�����x�N�g���ɂ���
			auto normal = contactPoint.normal;

			auto velocityA = bodyA->velocity + Vector3::Cross(Vector3(0, 0, bodyA->angularVelocity.z * MyMath::DEG_TO_RAD), r1);
			auto velocityB = bodyB->velocity + Vector3::Cross(Vector3(0, 0, bodyB->angularVelocity.z * MyMath::DEG_TO_RAD), r2);

			//2�̕��̂̑��Α��x�����߂�iV1 - V2�j
			auto relativeVelocity = velocityA - velocityB;

			//�ڐ��x�N�g���p�ϐ�
			Vector3 tangent1 = Matrix::GetMRoteZ(90) * normal;

			auto restitution = 0.5f * ((bodyA ? bodyA->restritution : 0.5f) + (bodyB ? bodyB->restritution : 0.5f));

			auto axis = normal;

			//rhs = Right Hand Side = �E��
			contactPoint.constraints[0].jacDiagInv = 1.0f / (
				(solverBodyA.massInv + solverBodyB.massInv)
				+ Vector3::Dot(axis, Vector3::Cross(Vector3::Cross(r1, axis) * solverBodyA.inertiaInv, r1))
				+ Vector3::Dot(axis, Vector3::Cross(Vector3::Cross(r2, axis) * solverBodyB.inertiaInv, r2))
				);
			contactPoint.constraints[0].rhs = -((1 + restitution) * Vector3::Dot(relativeVelocity, axis));
			contactPoint.constraints[0].rhs -= (bias * std::max<float>(0.0, contactPoint.distance + slop)) / timeStep; // position error
			contactPoint.constraints[0].rhs *= contactPoint.constraints[0].jacDiagInv;
			contactPoint.constraints[0].lowerLimit = -(float)INT_MAX;
			contactPoint.constraints[0].upperLimit = 0;
			contactPoint.constraints[0].axis = axis;

			axis = tangent1;
			contactPoint.constraints[1].jacDiagInv = 1.0f / (
				(solverBodyA.massInv + solverBodyB.massInv)
				+ Vector3::Dot(axis, Vector3::Cross(Vector3::Cross(r1, axis) * solverBodyA.inertiaInv, r1))
				+ Vector3::Dot(axis, Vector3::Cross(Vector3::Cross(r2, axis) * solverBodyB.inertiaInv, r2))
				);
			contactPoint.constraints[1].rhs = -Vector3::Dot(relativeVelocity, axis);
			contactPoint.constraints[1].rhs *= contactPoint.constraints[1].jacDiagInv;
			contactPoint.constraints[1].axis = axis;
		}
	}

	//�S���̉��Z
	for (int iter = 0; iter < iteration; iter++) {
		for (auto hitInfo : hitInfos) {
			RigidBody* bodyA = hitInfo->c1->gameobject->GetComponent<RigidBody>();
			RigidBody* bodyB = hitInfo->c2->gameobject->GetComponent<RigidBody>();

			SolverBody& solverBodyA = bodyA->solverBody;
			SolverBody& solverBodyB = bodyB->solverBody;

			for (auto& contactPoint : hitInfo->contact.contactPoints) {
				auto cpA = contactPoint.pointA;
				auto cpB = contactPoint.pointB;

				auto r1 = cpA - bodyA->gameobject->transform->position;
				auto r2 = cpB - bodyB->gameobject->transform->position;


				for (int i = 0; i < 2; i++) {
					auto constraint = contactPoint.constraints[i];
					auto deltaImpulse = constraint.rhs;
					auto deltaVelocityA = solverBodyA.deltaLinearVelocity + Vector3::Cross(Vector3(0, 0, solverBodyA.deltaAngularVelocity.z), r1);
					auto deltaVelocityB = solverBodyB.deltaLinearVelocity + Vector3::Cross(Vector3(0, 0, solverBodyB.deltaAngularVelocity.z), r2);

					deltaImpulse -= constraint.jacDiagInv * Vector3::Dot(constraint.axis, deltaVelocityA - deltaVelocityB);

					auto oldImpulse = constraint.accumImpulse;
					constraint.accumImpulse = MyMath::Clamp(oldImpulse + deltaImpulse, constraint.lowerLimit, constraint.upperLimit);

					deltaImpulse = constraint.accumImpulse - oldImpulse;
					solverBodyA.deltaLinearVelocity += constraint.axis * (deltaImpulse * solverBodyA.massInv);
					solverBodyA.deltaAngularVelocity.z += deltaImpulse * solverBodyA.inertiaInv * Vector2::Cross(r1, constraint.axis);

					solverBodyB.deltaLinearVelocity -= constraint.axis * (deltaImpulse * solverBodyB.massInv);
					solverBodyB.deltaAngularVelocity.z -= deltaImpulse * solverBodyB.inertiaInv * Vector2::Cross(r2, constraint.axis);

					if (i == 0) {
						auto maxFriction = hitInfo->contact.friction * abs(contactPoint.constraints[0].accumImpulse);
						contactPoint.constraints[1].lowerLimit = -maxFriction;
						contactPoint.constraints[1].upperLimit = maxFriction;
					}
				}
			}
		}
	}

	std::vector<RigidBody*> rbs;
	for (GameObject* gameobject : SceneManager::GetNowScene()->gameobjects) {
		RigidBody* rb = gameobject->GetComponent<RigidBody>();	//�R���C�_�[�������擾
		if (rb) {
			rbs.push_back(rb);
		}
	}
	//���x���X�V
	for (auto rb : rbs) {
		if (rb) {
			rb->velocity += rb->solverBody.deltaLinearVelocity;
			rb->angularVelocity += rb->solverBody.deltaAngularVelocity * MyMath::RAD_TO_DEG;

			rb->solverBody.deltaLinearVelocity = Vector3::Zero();
			rb->solverBody.deltaAngularVelocity = Vector3::Zero();
		}
	}
}