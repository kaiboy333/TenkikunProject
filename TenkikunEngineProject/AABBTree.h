#pragma once

#include <vector>
#include "Collider.h"
#include "BinaryTree.h"
#include "BinaryTree.h"

class AABBTree
{
	public:
		static std::vector<std::pair<int, int>> GetHitPairCollidersIndex(std::vector<Collider*>& colliders);

	private:
		static BinaryNode<std::pair<Rect, std::vector<int>>>* MakeNode(std::vector<Collider*>& colliders, std::vector<int>& colliderIndexes);

		static BinaryTree<std::pair<Rect, std::vector<int>>>* MakeTree(std::vector<Collider*>& colliders);

		static std::pair<std::vector<int>, std::vector<int>> GetHalfColliders(std::vector<int>& colliderIndexes);
};

