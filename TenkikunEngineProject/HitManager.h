#pragma once

#include "Collider.h"
#include "SupportInfo.h"

class HitManager
{
	public:
		//ブロードフェーズをする際のやり方
		enum class BlodeMode {
			NONE,
			AABB_TREE,
		};
		static BlodeMode blodeMode;

		//衝突応答のめり込み解消方法
		enum class CollisionResponseType {
			Penalty,
			Constraint,
		};
		static CollisionResponseType collisionResponseType;

		static void HitCheck();

	private:
		static std::vector<std::pair<Collider*, Collider*>> BlodePhase(std::vector<Collider*>& colliders);
		static std::vector<SupportInfo*> NarrawPhase(std::vector<std::pair<Collider*, Collider*>>& hitPairColliders);

		static void Response(std::vector<SupportInfo*>& supportInfos);
};

