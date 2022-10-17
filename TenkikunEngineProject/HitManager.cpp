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
		std::vector<Collider*> objectColliders = gameobject->GetComponents<Collider>();	//コライダーたちを取得
		colliders.insert(colliders.end(), objectColliders.begin(), objectColliders.end());	//リストに一気に追加
	}

	LARGE_INTEGER beforeTime;
	LARGE_INTEGER nowTime;

	//開始時刻を記録
	QueryPerformanceCounter(&beforeTime);

	if (colliders.size() >= 2) {
		//バウンディングボックスを使った衝突判定
		auto hitPairColliders = BlodePhase(colliders);

		//実際の形状での衝突判定
		NarrawPhase(hitPairColliders);
	}

	// 今の時間を取得
	QueryPerformanceCounter(&nowTime);
	// (今の時間 - 前フレームの時間) / 周波数 = 経過時間(秒単位)
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
		//全く同じコライダーなら飛ばす
		if (hitPairCollider.first == hitPairCollider.second)
			continue;
		//同じゲームオブジェクトのコライダーなら飛ばす
		if (hitPairCollider.first->gameobject == hitPairCollider.second->gameobject)
			continue;

		if (GJK::IsHit(hitPairCollider.first, hitPairCollider.second)) {
			hitPairCollider.first->isHit = true;
			hitPairCollider.second->isHit = true;
		}
	}
}

HitManager::BlodeMode HitManager::blodeMode = HitManager::BlodeMode::AABB_TREE;