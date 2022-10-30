#include "AABBTree.h"
#include "Rect.h"
#include "Debug.h"

std::vector<std::pair<int, int>> AABBTree::GetHitPairCollidersIndex(std::vector<Collider*>& colliders)
{
	std::vector<std::pair<int, int>> hitPairColliderIndexes;

	//二分木作成
	auto bTree = MakeTree(colliders);

	for (int i = 0, len = (int)colliders.size(); i < len; i++) {
		auto collider = colliders[i];

		std::vector<BinaryNode<std::pair<Rect, std::vector<int>>>*> nodes = { bTree->GetRoot() };

		while ((int)nodes.size() != 0) {
			auto node = nodes[0];
			nodes.erase(nodes.begin());

			//nodeがnullなら飛ばす
			if (!node)
				continue;

			//コライダーのバウンディングボックスとノードのバウンディングボックスが当たるなら
			Rect r1 = collider->GetBoundingBox();
			Rect r2 = node->key.first;
			if (Rect::IsHit(r1, r2)) {
				//コライダーが一つで構成されているのなら
				if ((int)node->key.second.size() == 1) {
					//入れ替え違いのペアがないか探す
					bool isFind = false;
					for (auto& hitPair : hitPairColliderIndexes) {
						//入れ違いのペアなら
						if (hitPair.first == node->key.second[0] && hitPair.second == i) {
							isFind = true;
							break;
						}
					}
					//まだ追加していないものなら
					if (!isFind) {
						//衝突の可能性が高いのでリストに追加
						hitPairColliderIndexes.push_back(std::make_pair(i, node->key.second[0]));
					}
				}
				else {
					//左右の子ノード追加
					nodes.push_back(node->left);
					nodes.push_back(node->right);
				}
			}
		}
	}

	return hitPairColliderIndexes;
}

BinaryNode<std::pair<Rect, std::vector<int>>>* AABBTree::MakeNode(std::vector<Collider*>& colliders, std::vector<int>& colliderIndexes)
{
	Rect rect = Rect(0, 0, 0, 0);
	for (int i = 0, len = (int)colliderIndexes.size(); i < len; i++) {
		Collider* collider = colliders[colliderIndexes[i]];

		if (i == 0) {
			rect = collider->GetBoundingBox();
		}
		else {
			rect += collider->GetBoundingBox();
		}
	}

	return new BinaryNode(std::make_pair(rect, colliderIndexes));
}

BinaryTree<std::pair<Rect, std::vector<int>>>* AABBTree::MakeTree(std::vector<Collider*>& colliders)
{
	//rootを作る
	std::vector<int> colliderIndexes;
	for (int i = 0, len = (int)colliders.size(); i < len; i++) {
		colliderIndexes.push_back(i);
	}
	auto root = MakeNode(colliders, colliderIndexes);
	//binaryTreeに追加
	auto bTree = new BinaryTree(root);


	std::vector<BinaryNode<std::pair<Rect, std::vector<int>>>*> nodes = {root};
	while ((int)nodes.size() != 0) {
		auto node = nodes[0];
		nodes.erase(nodes.begin());

		//コライダーの数が2個以上なら
		if ((int)node->key.second.size() >= 2) {
			//コライダーを二分割
			auto pair = GetHalfColliders(node->key.second);

			//左のノード作成
			auto left = MakeNode(colliders, pair.first);
			//ノードの子としてセット
			node->left = left;
			//リストに追加
			nodes.push_back(left);

			//右のノード作成
			auto right = MakeNode(colliders, pair.second);
			//ノードの子としてセット
			node->right = right;
			//リストに追加
			nodes.push_back(right);
		}
	}

	return bTree;
}

std::pair<std::vector<int>, std::vector<int>> AABBTree::GetHalfColliders(std::vector<int>& colliderIndexes)
{
	int len = (int)colliderIndexes.size();
	int halfLen = len / 2;

	std::vector<int> colliders1, colliders2;

	colliders1.insert(colliders1.end(), colliderIndexes.begin(), colliderIndexes.begin() + halfLen);
	colliders2.insert(colliders2.end(), colliderIndexes.begin() + halfLen, colliderIndexes.begin() + len);

	return std::make_pair(colliders1, colliders2);
}
