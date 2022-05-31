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

	void UpdateStairNo();	//ŠK‘w‚ðXV

	int GetStairNo();	//ŠK‘w‚ðŽæ“¾

	private:
		//ŠK‘w‚Ì[‚³
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

		//ƒŠƒXƒg‚Ìæ“ª‚Ì—v‘f‚ðŽæ“¾Aíœ
		TreeNode* node = nodes[0];
		nodes.erase(nodes.begin());

		//ŠK‘w‚ðƒZƒbƒg
		node->stairNo = node->parentNode ? node->parentNode->stairNo + 1 : 0;

		//Žq‚ç‚ð’Ç‰Á
		nodes.insert(nodes.end(), node->childNodes.begin(), node->childNodes.end());
	}
}

inline int TreeNode::GetStairNo()
{
	return stairNo;
}

