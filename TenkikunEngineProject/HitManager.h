#pragma once

#include "Collider.h"
#include "Physics.h"
#include "RigidBody.h"
#include "Collision.h"
#include <set>

class HitManager
{
	public:
		float timeStep = 0;
		const float bias = 0.1f;
		const float slop = 0.001f;
		const int iteration = 10;

		//ブロードフェーズをする際のやり方
		enum class BlodeMode {
			NONE,
			AABB_TREE,
			SWEEP_AND_PRUNE,
		};
		BlodeMode blodeMode = BlodeMode::SWEEP_AND_PRUNE;

		void HitCheck();
		void CallHitFunction(std::set<std::pair<Collision*, Collision*>>& beforeOnCollisions, std::set<std::pair<Collider*, Collider*>>& beforeOnTriggers);

	private:
		std::vector<RigidBody*> rigidBodies;
		std::vector<Collider*> colliders;

		std::vector<std::pair<int, int>> colliderPairs;
		std::vector<SupportInfo*> supportInfos;

		std::set<std::pair<Collision*, Collision*>> onCollisions;
		std::set<std::pair<Collider*, Collider*>> onTriggers;

		void BlodePhase();
		void NarrawPhase();

		void Response();
};
