#pragma once

#include "Collider.h"

class HitManager
{
	public:
		//�u���[�h�t�F�[�Y������ۂ̂���
		enum class BlodeMode {
			NONE,
			AABB_TREE,
		};

		static BlodeMode blodeMode;

		static void HitCheck();

	private:
		static std::vector<std::pair<Collider*, Collider*>> BlodePhase(std::vector<Collider*>& colliders);
		static void NarrawPhase(std::vector<std::pair<Collider*, Collider*>>& hitPairColliders);
};

