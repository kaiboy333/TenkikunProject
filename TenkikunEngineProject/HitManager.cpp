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
	for (GameObject* gameobject : SceneManager::GetNowScene()->gameobjects) {
		std::vector<Collider*> objectColliders = gameobject->GetComponents<Collider>();	//コライダーたちを取得
		colliders.insert(colliders.end(), objectColliders.begin(), objectColliders.end());	//リストに一気に追加

		//剛体を取得
		RigidBody* rigidBody = gameobject->GetComponent<RigidBody>();
		if (rigidBody) {
			rigidBodies.push_back(rigidBody);
		}
	}

	LARGE_INTEGER beforeTime;
	LARGE_INTEGER nowTime;

	//開始時刻を記録
	QueryPerformanceCounter(&beforeTime);

	if (colliders.size() >= 2) {
		//バウンディングボックスを使った衝突判定
		BlodePhase();

		//実際の形状での衝突判定
		NarrawPhase();

		//衝突応答
		Response();
	}

	// 今の時間を取得
	QueryPerformanceCounter(&nowTime);
	// (今の時間 - 前フレームの時間) / 周波数 = 経過時間(秒単位)
	double frameTime = static_cast<double>(nowTime.QuadPart - beforeTime.QuadPart) / static_cast<double>(Time::timeFreq.QuadPart);

	Debug::Log(std::to_string(frameTime));
}

void HitManager::BlodePhase()
{
	if (blodeMode == BlodeMode::AABB_TREE) {
		AABBTree aabbTree = AABBTree();
		colliderPairs = aabbTree.GetHitPairCollidersIndex(colliders);
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

		//全く同じコライダーなら飛ばす
		if (c1 == c2)
			continue;
		//同じゲームオブジェクトのコライダーなら飛ばす
		if (c1->gameobject == c2->gameobject)
			continue;

		auto supportInfo = GJK::IsHit(colliders, colliderPair.first, colliderPair.second);
		if (supportInfo) {
			c1->isHit = true;
			c2->isHit = true;
			supportInfos.push_back(supportInfo);
		}
	}
}

void HitManager::Response() {
	timeStep = Time::GetDeltaTime();

	std::vector<HitInfo*> hitInfos;

	for (auto& supportInfo : supportInfos) {
		auto hitInfo = EPA::GetHitInfo(colliders, supportInfo);
		//衝突応答を行うなら
		if (hitInfo) {
			//リストに追加
			hitInfos.push_back(hitInfo);
		}
	}

	//ソルバー用プロキシを作成
	for (auto hitInfo : hitInfos) {
		for (int i = 0, len = (int)rigidBodies.size(); i < len; i++) {
			//ソルバーボディにパラメータをセット
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

	//拘束のセットアップ
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

			//いったん衝突法線を3次元ベクトルにする
			auto normal = contactPoint->normal;

			auto velocityA = bodyA ? bodyA->velocity + Vector3::Cross(Vector3(0, 0, bodyA->angularVelocity.z * MyMath::DEG_TO_RAD), r1) : Vector3::Zero();
			auto velocityB = bodyB ? bodyB->velocity + Vector3::Cross(Vector3(0, 0, bodyB->angularVelocity.z * MyMath::DEG_TO_RAD), r2) : Vector3::Zero();

			//2つの物体の相対速度を求める（V1 - V2）
			auto relativeVelocity = velocityA - velocityB;

			//接線ベクトル用変数
			Vector3 tangent1 = Matrix::GetMRoteZ(90) * normal;

			auto restitution = 0.5f * ((bodyA ? bodyA->restritution : 0.5f) + (bodyB ? bodyB->restritution : 0.5f));

			auto axis = normal;

			//rhs = Right Hand Side = 右辺
			contactPoint->constraints[0].jacDiagInv = 1.0f / (
				(solverBodyA->massInv + solverBodyB->massInv)
				+ Vector3::Dot(axis, Vector3::Cross(Vector3::Cross(r1, axis) * solverBodyA->inertiaInv, r1))
				+ Vector3::Dot(axis, Vector3::Cross(Vector3::Cross(r2, axis) * solverBodyB->inertiaInv, r2))
				);
			contactPoint->constraints[0].rhs = -((1 + restitution) * Vector3::Dot(relativeVelocity, axis));
			contactPoint->constraints[0].rhs -= (bias * std::max<float>(0.0, contactPoint->distance + slop)) / timeStep; // position error
			contactPoint->constraints[0].rhs *= contactPoint->constraints[0].jacDiagInv;
			contactPoint->constraints[0].lowerLimit = -(float)INT_MAX;
			contactPoint->constraints[0].upperLimit = 0;
			contactPoint->constraints[0].axis = axis;

			axis = tangent1;
			contactPoint->constraints[1].jacDiagInv = 1.0f / (
				(solverBodyA->massInv + solverBodyB->massInv)
				+ Vector3::Dot(axis, Vector3::Cross(Vector3::Cross(r1, axis) * solverBodyA->inertiaInv, r1))
				+ Vector3::Dot(axis, Vector3::Cross(Vector3::Cross(r2, axis) * solverBodyB->inertiaInv, r2))
				);
			contactPoint->constraints[1].rhs = -Vector3::Dot(relativeVelocity, axis);
			contactPoint->constraints[1].rhs *= contactPoint->constraints[1].jacDiagInv;
			contactPoint->constraints[1].axis = axis;
		}

		//いらないsolverBodyを解放
		if (!bodyA) {
			delete(solverBodyA);
			solverBodyA = nullptr;
		}
		if (!bodyB) {
			delete(solverBodyB);
			solverBodyB = nullptr;
		}
	}

	//拘束の演算
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
					auto constraint = contactPoint->constraints[i];
					auto deltaImpulse = constraint.rhs;
					auto deltaVelocityA = solverBodyA->deltaLinearVelocity + Vector3::Cross(Vector3(0, 0, solverBodyA->deltaAngularVelocity.z), r1);
					auto deltaVelocityB = solverBodyB->deltaLinearVelocity + Vector3::Cross(Vector3(0, 0, solverBodyB->deltaAngularVelocity.z), r2);

					deltaImpulse -= constraint.jacDiagInv * Vector3::Dot(constraint.axis, deltaVelocityA - deltaVelocityB);

					auto oldImpulse = constraint.accumImpulse;
					constraint.accumImpulse = MyMath::Clamp(oldImpulse + deltaImpulse, constraint.lowerLimit, constraint.upperLimit);

					deltaImpulse = constraint.accumImpulse - oldImpulse;
					solverBodyA->deltaLinearVelocity += constraint.axis * (deltaImpulse * solverBodyA->massInv);
					solverBodyA->deltaAngularVelocity.z += deltaImpulse * solverBodyA->inertiaInv * Vector2::Cross(r1, constraint.axis);

					solverBodyB->deltaLinearVelocity -= constraint.axis * (deltaImpulse * solverBodyB->massInv);
					solverBodyB->deltaAngularVelocity.z -= deltaImpulse * solverBodyB->inertiaInv * Vector2::Cross(r2, constraint.axis);

					if (i == 0) {
						auto maxFriction = hitInfo->contact->friction * abs(contactPoint->constraints[0].accumImpulse);
						contactPoint->constraints[1].lowerLimit = -maxFriction;
						contactPoint->constraints[1].upperLimit = maxFriction;
					}
				}
			}

			//いらないsolverBodyを解放
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

	//Collisionを追加
	for (auto hitInfo : hitInfos) {
		Collision* collision1 = new Collision(colliders[hitInfo->colliderID2], hitInfo->contact);
		Collision* collision2 = new Collision(colliders[hitInfo->colliderID1], hitInfo->contact);
	}


	//速度を更新
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