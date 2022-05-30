#pragma once

#include <iostream>
#include <vector>

class TreeNode
{
public:
	std::vector<TreeNode*> childNodes;
	TreeNode* parentNode = nullptr;

	std::string element;

	TreeNode(std::string e, int stairNo = 0);

	bool isOpen = true;

	//ŠK‘w‚Ì[‚³
	int stairNo = 0;

	private:
};

inline TreeNode::TreeNode(std::string e, int stairNo)
{
	element = e;
	this->stairNo = stairNo;
}

