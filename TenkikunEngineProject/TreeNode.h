#pragma once

#include <iostream>
#include <vector>
#include "TriggerRect.h"
#include "TreeList.h"

class TreeList;
class TreeNode : public TriggerRect
{
public:
	std::vector<TreeNode*> childNodes;
	TreeNode* parentNode = nullptr;

	bool isOpen = true;

	TreeList* treeList = nullptr;

	//�e����q�̗]��
	float tabSpace = 18;

	//�A�C�R���̕�
	float iconWidth = 18;

	TreeNode(std::string e, TreeList* treeList);

	int GetStairNo();	//�K�w���擾
	void SetStairNo(int stairNo);	//�K�w���Z�b�g

	int GetRow();	//�s�����擾

	void SetRow(int row);	//�s�����Z�b�g

	void SetElement(std::string element);
	std::string GetElement();

	void Draw();

	private:
		//�K�w�̐[��
		int stairNo = 0;

		//���s�ڂ�
		int row = 0;

		std::string element;
};
