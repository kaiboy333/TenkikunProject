#pragma once

#include "BlodePhase.h"
#include "BinaryTree.h"

class AABBTree : public BlodePhase
{
	public:
		AABBTree(std::vector<Collider*>& colliders);

		std::vector<std::pair<int, int>> GetHitPairCollidersIndex() override;


	private:

		BinaryNode<std::pair<Rect, std::vector<int>>>* MakeNode(std::vector<int>& rectIndexes);

		BinaryTree<std::pair<Rect, std::vector<int>>>* MakeTree();

		std::pair<std::vector<int>, std::vector<int>> GetHalfColliders(std::vector<int>& colliderIndexes);

		std::vector<std::pair<Rect, std::vector<int>>> SortRect(std::vector<Collider*>& colliders);
};

