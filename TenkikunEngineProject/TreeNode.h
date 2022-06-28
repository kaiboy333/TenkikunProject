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
	WindowButton* button = nullptr;	//ボタン

	TreeNode(std::string e, TreeList* treeList, bool isOpen);

	int GetStairNo();	//階層を取得
	void SetStairNo(int stairNo);	//階層をセット

	int GetRow();	//行数を取得
	void SetRow(int row);	//行数をセット

	void SetElement(std::string element);
	std::string GetElement();

	vector<string> GetPathes();	//rootから自身までのパスを取得

	void Draw();

	private:
		//階層の深さ
		int stairNo = 0;

		//何行目か
		int row = 0;

		std::string element;
};
