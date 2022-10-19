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
		auto supportInfos = NarrawPhase(hitPairColliders);

		Response(supportInfos);
	}

	// 今の時間を取得
	QueryPerformanceCounter(&nowTime);
	// (今の時間 - 前フレームの時間) / 周波数 = 経過時間(秒単位)
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
		//全く同じコライダーなら飛ばす
		if (hitPairCollider.first == hitPairCollider.second)
			continue;
		//同じゲームオブジェクトのコライダーなら飛ばす
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
		//衝突応答を行うなら
		if (hitInfo) {
			//リストに追加
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

		float e = 1;	//反発係数
		auto m1Inv = rb1 ? (1 / rb1->mass) : 0;	//質量の逆数
		auto m2Inv = rb2 ? (1 / rb2->mass) : 0;	//質量の逆数
		auto r1 = hitInfo->contactPoint - c1->gameobject->transform->position;	//重心から衝突点までのベクトル
		auto r2 = hitInfo->contactPoint - c2->gameobject->transform->position;	//重心から衝突点までのベクトル
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
			//並進運動
			rb1->AddForce(f1, RigidBody::ForceMode::Impulse);
			//回転運動
			rb1->angularVelocity += t1 * i1Inv;
		}
		if (rb2) {
			//並進運動
			rb2->AddForce(f2, RigidBody::ForceMode::Impulse);
			//回転運動
			rb2->angularVelocity += t2 * i2Inv;
		}
	}
}


HitManager::BlodeMode HitManager::blodeMode = HitManager::BlodeMode::AABB_TREE;

HitManager::CollisionResponseType HitManager::collisionResponseType = HitManager::CollisionResponseType::Penalty;