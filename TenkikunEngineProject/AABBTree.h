#pragma once

#include <vector>
#include "Collider.h"
#include "BinaryTree.h"
#include "BinaryTree.h"

class AABBTree
{
	public:
		static std::vector<std::pair<Collider*, Collider*>> GetHitPairColliders(std::vector<Collider*>& colliders);

	private:
		static BinaryNode<std::pair<Rect, std::vector<Collider*>>>* MakeNode(std::vector<Collider*>& colliders);

		static BinaryTree<std::pair<Rect, std::vector<Collider*>>>* MakeTree(std::vector<Collider*>& colliders);

		static std::pair<std::vector<Collider*>, std::vector<Collider*>> GetHalfColliders(std::vector<Collider*>& colliders);	//colliders‚ð”¼•ª‚É‚µ‚ÄŽæ“¾
};

