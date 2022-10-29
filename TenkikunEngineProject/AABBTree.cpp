#include "AABBTree.h"
#include "Rect.h"
#include "Debug.h"

std::vector<std::pair<Collider*, Collider*>> AABBTree::GetHitPairColliders(std::vector<Collider*>& colliders)
{
	std::vector<std::pair<Collider*, Collider*>> hitPairColiiders;

	//�񕪖؍쐬
	auto bTree = MakeTree(colliders);

	for (auto& collider : colliders) {
		std::vector<BinaryNode<std::pair<Rect, std::vector<Collider*>>>*> nodes = { bTree->GetRoot() };
		while ((int)nodes.size() != 0) {
			auto node = nodes[0];
			nodes.erase(nodes.begin());

			//node��null�Ȃ��΂�
			if (!node)
				continue;

			//�R���C�_�[�̃o�E���f�B���O�{�b�N�X�ƃm�[�h�̃o�E���f�B���O�{�b�N�X��������Ȃ�
			Rect r1 = collider->GetBoundingBox();
			Rect r2 = node->key.first;
			if (Rect::IsHit(r1, r2)) {
				//�R���C�_�[����ō\������Ă���̂Ȃ�
				if ((int)node->key.second.size() == 1) {
					//����ւ��Ⴂ�̃y�A���Ȃ����T��
					bool isFind = false;
					for (auto& hitPairCollider : hitPairColiiders) {
						//����Ⴂ�̃y�A�Ȃ�
						if (hitPairCollider.first == node->key.second[0] && hitPairCollider.second == collider) {
							isFind = true;
							break;
						}
					}
					//�܂��ǉ����Ă��Ȃ����̂Ȃ�
					if (!isFind) {
						//�Փ˂̉\���������̂Ń��X�g�ɒǉ�
						hitPairColiiders.push_back(std::make_pair(collider, node->key.second[0]));
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

	return hitPairColiiders;
}

BinaryNode<std::pair<Rect, std::vector<Collider*>>>* AABBTree::MakeNode(std::vector<Collider*>& colliders)
{
	Rect rect = Rect(0, 0, 0, 0);
	for (int i = 0, len = (int)colliders.size(); i < len; i++) {
		Collider* collider = colliders[i];

		if (i == 0) {
			rect = collider->GetBoundingBox();
		}
		else {
			rect += collider->GetBoundingBox();
		}
	}

	return new BinaryNode(std::make_pair(rect, colliders));
}

BinaryTree<std::pair<Rect, std::vector<Collider*>>>* AABBTree::MakeTree(std::vector<Collider*>& colliders)
{
	//root�����
	auto root = MakeNode(colliders);
	//binaryTree�ɒǉ�
	auto bTree = new BinaryTree(root);


	std::vector<BinaryNode<std::pair<Rect, std::vector<Collider*>>>*> nodes = { root };
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

std::pair<std::vector<Collider*>, std::vector<Collider*>> AABBTree::GetHalfColliders(std::vector<Collider*>& colliders)
{
	int len = (int)colliders.size();
	int halfLen = len / 2;

	std::vector<Collider*> colliders1, colliders2;

	colliders1.insert(colliders1.end(), colliders.begin(), colliders.begin() + halfLen);
	colliders2.insert(colliders2.end(), colliders.begin() + halfLen, colliders.begin() + len);

	return std::make_pair(colliders1, colliders2);
}
