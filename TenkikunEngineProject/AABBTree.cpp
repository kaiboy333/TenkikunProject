#include "AABBTree.h"
#include "Rect.h"
#include "Debug.h"

AABBTree::AABBTree(std::vector<Collider*>& colliders) : BlodePhase(colliders)
{
}

std::vector<std::pair<int, int>> AABBTree::GetHitPairCollidersIndex()
{
	std::vector<std::pair<int, int>> hitPairColliderIndexes;

	//�񕪖؍쐬
	auto bTree = MakeTree();

	for (int i = 0, len = (int)rects.size(); i < len; i++) {
		std::vector<BinaryNode<std::pair<Rect, std::vector<int>>>*> nodes = { bTree->GetRoot() };

		while ((int)nodes.size() != 0) {
			auto node = nodes[0];
			nodes.erase(nodes.begin());

			//node��null�Ȃ��΂�
			if (!node)
				continue;

			//�R���C�_�[�̃o�E���f�B���O�{�b�N�X�ƃm�[�h�̃o�E���f�B���O�{�b�N�X��������Ȃ�
			Rect& r1 = rects[i];
			Rect& r2 = node->key.first;
			if (Rect::IsHit(r1, r2)) {
				//�R���C�_�[����ō\������Ă���̂Ȃ�
				if ((int)node->key.second.size() == 1) {
					//����ւ��Ⴂ�̃y�A���Ȃ����T��
					bool isFind = false;
					for (auto& hitPair : hitPairColliderIndexes) {
						//����Ⴂ�̃y�A�Ȃ�
						if (hitPair.first == node->key.second[0] && hitPair.second == i) {
							isFind = true;
							break;
						}
					}
					//�܂��ǉ����Ă��Ȃ����̂Ȃ�
					if (!isFind) {
						//�Փ˂̉\���������̂Ń��X�g�ɒǉ�
						hitPairColliderIndexes.push_back(std::make_pair(i, node->key.second[0]));
					}
				}
				else {
					//���E�̎q�m�[�h�ǉ�
					nodes.push_back(node->left);
					nodes.push_back(node->right);
				}
			}
		}
	}

	return hitPairColliderIndexes;
}

BinaryNode<std::pair<Rect, std::vector<int>>>* AABBTree::MakeNode(std::vector<int>& rectIndexes)
{
	Rect rect = Rect(0, 0, 0, 0);
	for (int i = 0, len = (int)rectIndexes.size(); i < len; i++) {
		Rect nowRect = rects[rectIndexes[i]];
		if (i == 0) {
			rect = nowRect;
		}
		else {
			rect += nowRect;
		}
	}

	return new BinaryNode(std::make_pair(rect, rectIndexes));
}

BinaryTree<std::pair<Rect, std::vector<int>>>* AABBTree::MakeTree()
{
	//root�����
	std::vector<int> rectIndexes;
	for (int i = 0, len = (int)rects.size(); i < len; i++) {
		rectIndexes.push_back(i);
	}
	auto root = MakeNode(rectIndexes);
	//binaryTree�ɒǉ�
	auto bTree = new BinaryTree(root);


	std::vector<BinaryNode<std::pair<Rect, std::vector<int>>>*> nodes = {root};
	while ((int)nodes.size() != 0) {
		auto node = nodes[0];
		nodes.erase(nodes.begin());

		//�R���C�_�[�̐���2�ȏ�Ȃ�
		if ((int)node->key.second.size() >= 2) {
			//�R���C�_�[��񕪊�
			auto pair = GetHalfColliders(node->key.second);

			//���̃m�[�h�쐬
			auto left = MakeNode(pair.first);
			//�m�[�h�̎q�Ƃ��ăZ�b�g
			node->left = left;
			//���X�g�ɒǉ�
			nodes.push_back(left);

			//�E�̃m�[�h�쐬
			auto right = MakeNode(pair.second);
			//�m�[�h�̎q�Ƃ��ăZ�b�g
			node->right = right;
			//���X�g�ɒǉ�
			nodes.push_back(right);
		}
	}

	return bTree;
}

std::pair<std::vector<int>, std::vector<int>> AABBTree::GetHalfColliders(std::vector<int>& rectIndexes)
{
	int len = (int)rectIndexes.size();
	int halfLen = len / 2;

	std::vector<int> colliders1, colliders2;

	colliders1.insert(colliders1.end(), rectIndexes.begin(), rectIndexes.begin() + halfLen);
	colliders2.insert(colliders2.end(), rectIndexes.begin() + halfLen, rectIndexes.begin() + len);

	return std::make_pair(colliders1, colliders2);
}

std::vector<std::pair<Rect, std::vector<int>>> AABBTree::SortRect(std::vector<Collider*>& colliders)
{
	return std::vector<std::pair<Rect, std::vector<int>>>();
}
