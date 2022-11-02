#pragma once

#include "Collider.h"
#include "SupportInfo.h"
#include "Physics.h"
#include "RigidBody.h"
#include "Collision.h"
#include <set>

class HitManager
{
	public:
		static float timeStep;
		static const float bias;
		static const float slop;
		static const int iteration;

		//ブロードフェーズをする際のやり方
		enum class BlodeMode {
			NONE,
			AABB_TREE,
		};
		static BlodeMode blodeMode;

		static void HitCheck();

	private:
		static std::vector<RigidBody*> rigidBodies;
		static std::vector<Collider*> colliders;

		static std::vector<std::pair<int, int>> colliderPairs;
		static std::vector<SupportInfo*> supportInfos;

		static std::set<std::pair<Collision*, Collision*>> onCollisions;
		static std::set<std::pair<Collision*, Collision*>>* beforeOnCollisions;
		static std::set<std::pair<Collider*, Collider*>> onTriggers;
		static std::set<std::pair<Collider*, Collider*>>* beforeOnTriggers;

		static void BlodePhase();
		static void NarrawPhase();

		static void Response();

		static void CallHitFunction();
};
