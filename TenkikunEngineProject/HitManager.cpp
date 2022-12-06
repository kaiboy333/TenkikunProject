#include "HitManager.h"
#include "Collider.h"
#include "GJK.h"
#include "AABBTree.h"
#include "Time.h"
#include "Debug.h"
#include "EPA.h"
#include "RigidBody.h"
#include "MonoBehaviour.h"
#include "SweepAndPrune.h"

void HitManager::HitCheck()
{
	rigidBodies.clear();
	colliderPairs.clear();
	colliders.clear();
	supportInfos.clear();

	for (GameObject* gameobject : SceneManager::GetNowScene()->gameobjects) {
		std::vector<Collider*> objectColliders = gameobject->GetComponents<Collider>();	//�R���C�_�[�������擾
		colliders.insert(colliders.end(), objectColliders.begin(), objectColliders.end());	//���X�g�Ɉ�C�ɒǉ�

		//���̂��擾
		RigidBody* rigidBody = gameobject->GetComponent<RigidBody>();
		if (rigidBody) {
			rigidBodies.push_back(rigidBody);
		}
	}

	//float timeAll1 = Time::GetTime();

	if (colliders.size() >= 2) {
		//float time0 = Time::GetTime();

		//�o�E���f�B���O�{�b�N�X���g�����Փ˔���
		BlodePhase();

		//float time1 = Time::GetTime();

		//���ۂ̌`��ł̏Փ˔���
		NarrawPhase();

		//float time2 = Time::GetTime();

		//�Փˉ���
		Response();

		//float time5 = Time::GetTime();
		//Debug::Log("blodephase" + std::to_string(time1 - time0));
		//Debug::Log("narrowphase" + std::to_string(time2 - time1));
		//Debug::Log("response" + std::to_string(time5 - time2));
	}

	//float timeAll2 = Time::GetTime();

	//Debug::Log("HIt:" + std::to_string(timeAll2 - timeAll1));
}

void HitManager::BlodePhase()
{
	if (blodeMode == BlodeMode::AABB_TREE) {
		auto aabbTree = AABBTree(colliders);
		colliderPairs = aabbTree.GetHitPairCollidersIndex();
	}
	else if (blodeMode == BlodeMode::SWEEP_AND_PRUNE) {
		auto sweepAndPrune = SweepAndPrune(colliders);
		colliderPairs = sweepAndPrune.GetHitPairCollidersIndex();
	}
	else if (blodeMode == BlodeMode::NONE) {

		for (int i = 0, len = (int)colliders.size(); i < len; i++) {
			for (int j = 0; j < len; j++) {
				colliderPairs.push_back({i, j});
			}
		}
	}
}

void HitManager::NarrawPhase()
{
	for (auto& colliderPair : colliderPairs) {
		auto c1 = colliders[colliderPair.first];
		auto c2 = colliders[colliderPair.second];

		//�S�������R���C�_�[�Ȃ��΂�
		if (c1 == c2)
			continue;
		//�����Q�[���I�u�W�F�N�g�̃R���C�_�[�Ȃ��΂�
		if (c1->gameobject == c2->gameobject)
			continue;

		auto supportInfo = GJK::IsHit(colliders, colliderPair.first, colliderPair.second);
		if (supportInfo) {
			c1->isHit = true;
			c2->isHit = true;
			//���蔲���Ȃ��Ȃ�
			if (!c1->isTrigger && !c2->isTrigger) {
				//���X�g�ɒǉ�
				supportInfos.push_back(supportInfo);
			}
			else {
				//onTriggers�ɒǉ�
				if (*c1 < *c2) {
					onTriggers.insert(std::make_pair(c1, c2));
				}
				else {
					onTriggers.insert(std::make_pair(c2, c1));
				}
			}
		}
	}
}

void HitManager::Response() {
	timeStep = Time::GetDeltaTime();

	std::list<HitInfo*> hitInfos;

	//float time3 = Time::GetTime();

	for (auto supportInfo : supportInfos) {
		//float time5 = Time::GetTime();

		auto hitInfo = EPA::GetHitInfo(colliders, supportInfo);
		//�Փˉ������s���Ȃ�
		if (hitInfo) {
			//���X�g�ɒǉ�
			hitInfos.emplace_back(hitInfo);
		}

		float time6 = Time::GetTime();
		//Debug::Log("EPA8:" + std::to_string(time6 - time5));
	}

	//float time4 = Time::GetTime();
	//Debug::Log("EPA:" + std::to_string(time4 - time3));

	//�\���o�[�p�v���L�V���쐬
	for (auto hitInfo : hitInfos) {
		for (int i = 0, len = (int)rigidBodies.size(); i < len; i++) {
			//�\���o�[�{�f�B�Ƀp�����[�^���Z�b�g
			RigidBody* rigidBody = rigidBodies[i];
			if (rigidBody) {
				if (rigidBody->bodyType == RigidBody::BodyType::Dynamic) {
					rigidBodies[i]->solverBody->massInv = 1 / rigidBodies[i]->mass;
					rigidBodies[i]->solverBody->inertiaInv = 1 / colliders[i]->GetI();
				}
				else {
					rigidBodies[i]->solverBody->massInv = 0;
					rigidBodies[i]->solverBody->inertiaInv = 0;
				}
			}
		}
	}

	//�S���̃Z�b�g�A�b�v
	for (auto hitInfo : hitInfos) {
		Collider* c1 = colliders[hitInfo->colliderID1];
		Collider* c2 = colliders[hitInfo->colliderID2];

		RigidBody* bodyA = c1->gameobject->GetComponent<RigidBody>();
		SolverBody* solverBodyA = bodyA ? bodyA->solverBody : new SolverBody();

		RigidBody* bodyB = c2->gameobject->GetComponent<RigidBody>();
		SolverBody* solverBodyB = bodyB ? bodyB->solverBody : new SolverBody();
		for (auto& contactPoint : hitInfo->contact->contactPoints) {
			auto cpA = contactPoint->pointA;
			auto cpB = contactPoint->pointB;

			auto r1 = cpA - c1->gameobject->transform->position;
			auto r2 = cpB - c2->gameobject->transform->position;

			//��������Փ˖@����3�����x�N�g���ɂ���
			auto normal = contactPoint->normal;

			auto velocityA = bodyA ? bodyA->velocity + Vector3::Cross(Vector3(0, 0, bodyA->angularVelocity.z * MyMath::DEG_TO_RAD), r1) : Vector3::Zero();
			auto velocityB = bodyB ? bodyB->velocity + Vector3::Cross(Vector3(0, 0, bodyB->angularVelocity.z * MyMath::DEG_TO_RAD), r2) : Vector3::Zero();

			//2�̕��̂̑��Α��x�����߂�iV1 - V2�j
			auto relativeVelocity = velocityA - velocityB;

			//�ڐ��x�N�g���p�ϐ�
			Vector3 tangent1 = Matrix::GetMRoteZ(90) * normal;

			auto restitution = 0.5f * ((bodyA ? bodyA->restritution : 0.5f) + (bodyB ? bodyB->restritution : 0.5f));

			auto axis = normal;

			//rhs = Right Hand Side = �E��
			auto sumMassInv = solverBodyA->massInv + solverBodyB->massInv;
			if (sumMassInv != 0) {
				contactPoint->constraints[0].jacDiagInv = 1.0f / (
					sumMassInv
					+ Vector3::Dot(axis, Vector3::Cross(Vector3::Cross(r1, axis) * solverBodyA->inertiaInv, r1))
					+ Vector3::Dot(axis, Vector3::Cross(Vector3::Cross(r2, axis) * solverBodyB->inertiaInv, r2))
				);
			}
			contactPoint->constraints[0].rhs = -((1 + restitution) * Vector3::Dot(relativeVelocity, axis));
			contactPoint->constraints[0].rhs -= (bias * std::max<float>(0.0, contactPoint->distance + slop)) / timeStep; // position error
			contactPoint->constraints[0].rhs *= contactPoint->constraints[0].jacDiagInv;
			contactPoint->constraints[0].lowerLimit = -(float)INT_MAX;
			contactPoint->constraints[0].upperLimit = 0;
			contactPoint->constraints[0].axis = axis;

			axis = tangent1;
			if (sumMassInv != 0) {
				contactPoint->constraints[1].jacDiagInv = 1.0f / (
					sumMassInv
					+ Vector3::Dot(axis, Vector3::Cross(Vector3::Cross(r1, axis) * solverBodyA->inertiaInv, r1))
					+ Vector3::Dot(axis, Vector3::Cross(Vector3::Cross(r2, axis) * solverBodyB->inertiaInv, r2))
				);
			}
			contactPoint->constraints[1].rhs = -Vector3::Dot(relativeVelocity, axis);
			contactPoint->constraints[1].rhs *= contactPoint->constraints[1].jacDiagInv;
			contactPoint->constraints[1].axis = axis;
		}

		//����Ȃ�solverBody�����
		if (!bodyA) {
			delete(solverBodyA);
			solverBodyA = nullptr;
		}
		if (!bodyB) {
			delete(solverBodyB);
			solverBodyB = nullptr;
		}
	}

	//�S���̉��Z
	for (int iter = 0; iter < iteration; iter++) {
		for (auto hitInfo : hitInfos) {
			Collider* c1 = colliders[hitInfo->colliderID1];
			Collider* c2 = colliders[hitInfo->colliderID2];

			RigidBody* bodyA = c1->gameobject->GetComponent<RigidBody>();
			SolverBody* solverBodyA = bodyA ? bodyA->solverBody : new SolverBody();

			RigidBody* bodyB = c2->gameobject->GetComponent<RigidBody>();
			SolverBody* solverBodyB = bodyB ? bodyB->solverBody : new SolverBody();

			for (auto& contactPoint : hitInfo->contact->contactPoints) {
				auto cpA = contactPoint->pointA;
				auto cpB = contactPoint->pointB;

				auto r1 = cpA - c1->gameobject->transform->position;
				auto r2 = cpB - c2->gameobject->transform->position;


				for (int i = 0; i < 2; i++) {
					auto& constraint = contactPoint->constraints[i];
					auto deltaImpulse = constraint.rhs;
					auto deltaVelocityA = solverBodyA->deltaLinearVelocity + Vector3::Cross(Vector3(0, 0, solverBodyA->deltaAngularVelocity.z), r1);
					auto deltaVelocityB = solverBodyB->deltaLinearVelocity + Vector3::Cross(Vector3(0, 0, solverBodyB->deltaAngularVelocity.z), r2);

					deltaImpulse -= constraint.jacDiagInv * Vector3::Dot(constraint.axis, deltaVelocityA - deltaVelocityB);

					auto oldImpulse = constraint.accumImpulse;
					constraint.accumImpulse = MyMath::Clamp(oldImpulse + deltaImpulse, constraint.lowerLimit, constraint.upperLimit);

					deltaImpulse = constraint.accumImpulse - oldImpulse;

					solverBodyA->deltaLinearVelocity += constraint.axis * (deltaImpulse * solverBodyA->massInv);
					solverBodyA->deltaAngularVelocity.z += deltaImpulse * solverBodyA->inertiaInv * Vector2::Cross(r1, constraint.axis);
					if (bodyA) {
						if (bodyA->constraints.freezePosition.x) {
							solverBodyA->deltaLinearVelocity.x = 0;
						}
						if (bodyA->constraints.freezePosition.y) {
							solverBodyA->deltaLinearVelocity.y = 0;
						}
						if (bodyA->constraints.freezeRotation.z) {
							solverBodyA->deltaAngularVelocity.z = 0;
						}
					}

					solverBodyB->deltaLinearVelocity -= constraint.axis * (deltaImpulse * solverBodyB->massInv);
					solverBodyB->deltaAngularVelocity.z -= deltaImpulse * solverBodyB->inertiaInv * Vector2::Cross(r2, constraint.axis);
					if (bodyB) {
						if (bodyB->constraints.freezePosition.x) {
							solverBodyB->deltaLinearVelocity.x = 0;
						}
						if (bodyB->constraints.freezePosition.y) {
							solverBodyB->deltaLinearVelocity.y = 0;
						}
						if (bodyB->constraints.freezeRotation.z) {
							solverBodyB->deltaAngularVelocity.z = 0;
						}
					}

					if (i == 0) {
						auto maxFriction = hitInfo->contact->friction * abs(contactPoint->constraints[0].accumImpulse);
						contactPoint->constraints[1].lowerLimit = -maxFriction;
						contactPoint->constraints[1].upperLimit = maxFriction;
					}
				}
			}

			//����Ȃ�solverBody�����
			if (!bodyA) {
				delete(solverBodyA);
				solverBodyA = nullptr;
			}
			if (!bodyB) {
				delete(solverBodyB);
				solverBodyB = nullptr;
			}
		}
	}

	//float time5 = Time::GetTime();
	//Debug::Log("Kousoku:" + std::to_string(time5 - time4));

	//Collision��ǉ�
	for (auto hitInfo : hitInfos) {
		Collision* collision1 = new Collision(colliders[hitInfo->colliderID2], hitInfo->contact);
		Collision* collision2 = new Collision(colliders[hitInfo->colliderID1], hitInfo->contact);

		//���̕����ԍ����Ⴍ�Ȃ�悤�ɂ���
		if (*collision1 < *collision2) {
			onCollisions.insert(std::make_pair(collision1, collision2));
		}
		else {
			onCollisions.insert(std::make_pair(collision2, collision1));
		}
	}


	//���x���X�V
	for (int i = 0, len = (int)rigidBodies.size(); i < len; i++) {
		RigidBody* rb = rigidBodies[i];
		SolverBody* sb = rb ? rb->solverBody : nullptr;

		if (rb) {
			rb->velocity += sb->deltaLinearVelocity;
			rb->angularVelocity += sb->deltaAngularVelocity * MyMath::RAD_TO_DEG;

			sb->deltaLinearVelocity = Vector3::Zero();
			sb->deltaAngularVelocity = Vector3::Zero();
		}
	}
}

void HitManager::CallHitFunction(std::set<std::pair<Collision*, Collision*>>& beforeOnCollisions, std::set<std::pair<Collider*, Collider*>>& beforeOnTriggers)
{
	//onCollision
	for (auto& onCollision : onCollisions) {
		bool isFind = false;
		auto iter = beforeOnCollisions.begin();
		for (auto& beforeCollision : beforeOnCollisions) {
			//��v������
			if (*beforeCollision.first == *onCollision.first && *beforeCollision.second == *onCollision.second) {
				isFind = true;
				break;
			}
			iter++;
		}
		//auto iter = std::find(beforeOnCollisions.begin(), beforeOnCollisions.end(), onCollision);
		//����������
		if (isFind) {
			//�O�ɂ��Փ˂��Ă���(Stay)
			//first
			for (auto mono : onCollision.first->gameobject->GetComponents<MonoBehaviour>()) {
				mono->OnColliderStay(onCollision.second);
			}
			//second
			for (auto mono : onCollision.second->gameobject->GetComponents<MonoBehaviour>()) {
				mono->OnColliderStay(onCollision.first);
			}
			//�O�̃��X�g����폜
			beforeOnCollisions.erase(iter);

			//Debug::Log("OnCollisionStay");
		}
		//������Ȃ�������
		else {
			//���߂ďՓ˂��Ă���(Enter)
			//first
			for (auto mono : onCollision.first->gameobject->GetComponents<MonoBehaviour>()) {
				mono->OnColliderEnter(onCollision.second);
			}
			//second
			for (auto mono : onCollision.second->gameobject->GetComponents<MonoBehaviour>()) {
				mono->OnColliderEnter(onCollision.first);
			}

			//Debug::Log("OnCollisionEnter");
		}
	}
	//�c���Ă���O�̏Փˏ���
	for (auto& beforeOnCollision : beforeOnCollisions) {
		//����Փ˂��Ȃ��Ȃ���(Exit)
		//first
		for (auto mono : beforeOnCollision.first->gameobject->GetComponents<MonoBehaviour>()) {
			mono->OnColliderExit(beforeOnCollision.second);
		}
		//second
		for (auto mono : beforeOnCollision.second->gameobject->GetComponents<MonoBehaviour>()) {
			mono->OnColliderExit(beforeOnCollision.first);
		}

		//Debug::Log("OnCollisionExit");
	}

	//onTrigger
	for (auto& onTrigger : onTriggers) {
		bool isFind = false;
		auto iter = beforeOnTriggers.begin();
		for (auto& beforeOnTrigger : beforeOnTriggers) {
			//��v������
			if (*beforeOnTrigger.first == *onTrigger.first && *beforeOnTrigger.second == *onTrigger.second) {
				isFind = true;
				break;
			}
			iter++;
		}
		//auto iter = std::find(beforeOnTriggers.begin(), beforeOnTriggers.end(), onTrigger);
		//����������
		if (isFind) {
			//�O�ɂ��Փ˂��Ă���(Stay)
			//first
			for (auto mono : onTrigger.first->gameobject->GetComponents<MonoBehaviour>()) {
				mono->OnTriggerStay(onTrigger.second);
			}
			//second
			for (auto mono : onTrigger.second->gameobject->GetComponents<MonoBehaviour>()) {
				mono->OnTriggerStay(onTrigger.first);
			}
			//�O�̃��X�g����폜
			beforeOnTriggers.erase(iter);

			//Debug::Log("OnTriggerStay");
		}
		//������Ȃ�������
		else {
			//���߂ďՓ˂��Ă���(Enter)
			//first
			for (auto mono : onTrigger.first->gameobject->GetComponents<MonoBehaviour>()) {
				mono->OnTriggerEnter(onTrigger.second);
			}
			//second
			for (auto mono : onTrigger.second->gameobject->GetComponents<MonoBehaviour>()) {
				mono->OnTriggerEnter(onTrigger.first);
			}
		}

		//Debug::Log("OnTriggerEnter");
	}
	//�c���Ă���O�̏Փˏ���
	for (auto& beforeOnTrigger : beforeOnTriggers) {
		//����Փ˂��Ȃ��Ȃ���(Exit)
		//first
		for (auto mono : beforeOnTrigger.first->gameobject->GetComponents<MonoBehaviour>()) {
			mono->OnTriggerExit(beforeOnTrigger.second);
		}
		//second
		for (auto mono : beforeOnTrigger.second->gameobject->GetComponents<MonoBehaviour>()) {
			mono->OnTriggerExit(beforeOnTrigger.first);
		}

		//Debug::Log("OnTriggerExit");
	}

	beforeOnCollisions = std::set<std::pair<Collision*, Collision*>>(onCollisions);
	beforeOnTriggers = std::set<std::pair<Collider*, Collider*>>(onTriggers);
}