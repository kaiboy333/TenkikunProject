#pragma once

#include <iostream>
#include <vector>

class TreeNode
{
public:
	std::vector<TreeNode*> childNodes;
	TreeNode* parentNode = nullptr;

	std::string element;

	bool isOpen = true;

	TreeNode(std::string e, int stairNo = 0);

	void UpdateStairNo();	//�K�w���X�V

	int GetStairNo();	//�K�w���擾

	private:
		//�K�w�̐[��
		int stairNo = 0;
};

inline TreeNode::TreeNode(std::string e, int stairNo)
{
	element = e;
	this->stairNo = stairNo;
}

inline void TreeNode::UpdateStairNo()
{
	std::vector<TreeNode*> nodes;
	nodes.push_back(this);

	while (nodes.size() != 0) {

		//���X�g�̐擪�̗v�f���擾�A�폜
		TreeNode* node = nodes[0];
		nodes.erase(nodes.begin());

		//�K�w���Z�b�g
		node->stairNo = node->parentNode ? node->parentNode->stairNo + 1 : 0;

		//�q���ǉ�
		nodes.insert(nodes.end(), node->childNodes.begin(), node->childNodes.end());
	}
}

inline int TreeNode::GetStairNo()
{
	return stairNo;
}

