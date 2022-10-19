#pragma once

#include "Collider.h"
#include "SupportInfo.h"

class HitManager
{
	public:
		//�u���[�h�t�F�[�Y������ۂ̂���
		enum class BlodeMode {
			NONE,
			AABB_TREE,
		};
		static BlodeMode blodeMode;

		//�Փˉ����̂߂荞�݉������@
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

