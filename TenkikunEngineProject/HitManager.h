#pragma once

#include "Collider.h"
#include "SupportInfo.h"
#include "Physics.h"
#include "RigidBody.h"

class HitManager
{
	public:
		float timeStep = 0;
		float bias = 0.1f;
		float slop = 0.001f;
		int iteration = 10;
		Vector3 gravity = Vector3(0, -9.8f, 0);

		//ブロードフェーズをする際のやり方
		enum class BlodeMode {
			NONE,
			AABB_TREE,
		};
		BlodeMode blodeMode = BlodeMode::AABB_TREE;

		void HitCheck();

	private:
		std::vector<RigidBody*> rigidBodies;
		std::vector<Collider*> colliders;

		std::vector<std::pair<int, int>> colliderPairs;
		std::vector<SupportInfo*> supportInfos;

		void BlodePhase();
		void NarrawPhase();

		void Response();
};
