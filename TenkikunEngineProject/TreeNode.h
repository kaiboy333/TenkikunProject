#pragma once

#include <iostream>
#include <vector>
#include "TriggerRect.h"
#include "TreeList.h"
#include "WindowButton.h"

class TreeList;
class TreeNode : public TriggerRect
{
public:
	std::vector<TreeNode*> childNodes;
	TreeNode* parentNode = nullptr;

	bool isOpen;

	TreeList* treeList = nullptr;
	WindowButton* button = nullptr;	//�{�^��

	TreeNode(std::string e, TreeList* treeList, bool isOpen);

	int GetStairNo();	//�K�w���擾
	void SetStairNo(int stairNo);	//�K�w���Z�b�g

	int GetRow();	//�s�����擾
	void SetRow(int row);	//�s�����Z�b�g

	void SetElement(std::string element);
	std::string GetElement();

	vector<string> GetPathes();	//root���玩�g�܂ł̃p�X���擾

	void Draw();

	private:
		//�K�w�̐[��
		int stairNo = 0;

		//���s�ڂ�
		int row = 0;

		std::string element;
};
