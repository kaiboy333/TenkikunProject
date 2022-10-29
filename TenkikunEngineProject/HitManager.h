#pragma once

#include "Collider.h"
#include "SupportInfo.h"

class HitManager
{
	public:
		float timeStep;
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
		std::vector<std::pair<Collider*, Collider*>> BlodePhase(std::vector<Collider*>& colliders);
		std::vector<SupportInfo*> NarrawPhase(std::vector<std::pair<Collider*, Collider*>>& hitPairColliders);

		void Response(std::vector<SupportInfo*>& supportInfos);
};
