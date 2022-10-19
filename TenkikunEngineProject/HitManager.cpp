#include "HitManager.h"
#include "Collider.h"
#include "GJK.h"
#include "AABBTree.h"
#include "Time.h"
#include "Debug.h"
#include "EPA.h"
#include "RigidBody.h"

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

void Response(std::vector<SupportInfo*>& supportInfos) {
	std::vector<HitInfo*> hitInfos;

	for (auto supportInfo : supportInfos) {
		auto hitInfo = EPA::GetHitInfo(supportInfo);
		//�Փˉ������s���Ȃ�
		if (hitInfo) {
			//���X�g�ɒǉ�
			hitInfos.push_back(hitInfo);
		}
	}

	for (auto hitInfo : hitInfos) {
		auto c1 = hitInfo->c1;
		auto c2 = hitInfo->c2;
		auto rb1 = c1->gameobject->GetComponent<RigidBody>();
		auto rb2 = c1->gameobject->GetComponent<RigidBody>();
		auto v1 = rb1 ? rb1->velocity : Vector3::Zero();
		auto v2 = rb2 ? rb2->velocity : Vector3::Zero();

		float e = 1;	//�����W��
		auto m1Inv = rb1 ? (1 / rb1->mass) : 0;	//���ʂ̋t��
		auto m2Inv = rb2 ? (1 / rb2->mass) : 0;	//���ʂ̋t��
		auto r1 = hitInfo->contactPoint - c1->gameobject->transform->position;	//�d�S����Փ˓_�܂ł̃x�N�g��
		auto r2 = hitInfo->contactPoint - c2->gameobject->transform->position;	//�d�S����Փ˓_�܂ł̃x�N�g��
		auto v12 = v2 - v1;
		auto i1Inv = rb1 ? c1->GetI() : 0;
		auto i2Inv = rb2 ? c2->GetI() : 0;
		auto n = hitInfo->n;
		
		auto j = ((1 + e) * Vector3::Dot(v12, n)) / (m1Inv + m2Inv + Vector3::Dot(Vector3::Cross(Vector3::Cross(r1, n) * i1Inv, r1) + Vector3::Cross((r2, n) * i2Inv, r2), n));
		auto f1 = n * j / Time::GetDeltaTime();
		auto t1 = Vector3::Cross(r1, f1);

		auto f2 = -f1;
		auto t2 = Vector3::Cross(r2, f2);

		if (rb1) {
			//���i�^��
			rb1->AddForce(f1, RigidBody::ForceMode::Impulse);
			//��]�^��
			rb1->angularVelocity += t1 * i1Inv;
		}
		if (rb2) {
			//���i�^��
			rb2->AddForce(f2, RigidBody::ForceMode::Impulse);
			//��]�^��
			rb2->angularVelocity += t2 * i2Inv;
		}
	}
}


HitManager::BlodeMode HitManager::blodeMode = HitManager::BlodeMode::AABB_TREE;

HitManager::CollisionResponseType HitManager::collisionResponseType = HitManager::CollisionResponseType::Penalty;