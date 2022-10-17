#include "HitManager.h"
#include "Collider.h"
#include "GJK.h"
#include "AABBTree.h"
#include "Time.h"
#include "Debug.h"

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
		NarrawPhase(hitPairColliders);
	}

	// ���̎��Ԃ��擾
	QueryPerformanceCounter(&nowTime);
	// (���̎��� - �O�t���[���̎���) / ���g�� = �o�ߎ���(�b�P��)
	double frameTime = static_cast<double>(nowTime.QuadPart - beforeTime.QuadPart) / static_cast<double>(Time::timeFreq.QuadPart);

	Debug::Log(std::to_string(frameTime));
}

std::vector<std::pair<Collider*, Collider*>> HitManager::BlodePhase(std::vector<Collider*>& colliders)
{
	if (blodeMode == BlodeMode::AABB_TREE) {
		return AABBTree::GetHitPairColliders(colliders);
	}
	else if (blodeMode == BlodeMode::NONE) {
		std::vector<std::pair<Collider*, Collider*>> pairs;

		for (auto& collider1 : colliders) {
			for (auto& collider2 : colliders) {
				pairs.push_back(std::make_pair(collider1, collider2));
			}
		}

		return pairs;
	}
}

void HitManager::NarrawPhase(std::vector<std::pair<Collider*, Collider*>>& hitPairColliders)
{
	for (auto& hitPairCollider : hitPairColliders) {
		//�S�������R���C�_�[�Ȃ��΂�
		if (hitPairCollider.first == hitPairCollider.second)
			continue;
		//�����Q�[���I�u�W�F�N�g�̃R���C�_�[�Ȃ��΂�
		if (hitPairCollider.first->gameobject == hitPairCollider.second->gameobject)
			continue;

		if (GJK::IsHit(hitPairCollider.first, hitPairCollider.second)) {
			hitPairCollider.first->isHit = true;
			hitPairCollider.second->isHit = true;
		}
	}
}

HitManager::BlodeMode HitManager::blodeMode = HitManager::BlodeMode::AABB_TREE;