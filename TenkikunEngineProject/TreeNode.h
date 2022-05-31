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

	void UpdateStairNo();	//階層を更新

	int GetStairNo();	//階層を取得

	private:
		//階層の深さ
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

		//リストの先頭の要素を取得、削除
		TreeNode* node = nodes[0];
		nodes.erase(nodes.begin());

		//階層をセット
		node->stairNo = node->parentNode ? node->parentNode->stairNo + 1 : 0;

		//子らを追加
		nodes.insert(nodes.end(), node->childNodes.begin(), node->childNodes.end());
	}
}

inline int TreeNode::GetStairNo()
{
	return stairNo;
}

