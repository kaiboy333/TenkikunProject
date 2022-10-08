#pragma once

#include "SceneManager.h"
#include "WindowManager.h"
#include "Window.h"
#include <iostream>
#include <vector>
#include <string>
#include "Property.h"
#include "TreeNode.h"
#include "ScrollRect.h"

class TreeNode;
class TreeList : public ScrollRect
{
public:
	//ボタン画像(開いていないのと開いているとき)
	Image* images[2];

	//親から子の余白
	float tabSpace = 12;

	bool isFirstOpen;	//ノード追加時に開けた状態で追加するか

	TreeList(float startX, float startY, float width, float height, bool isFirstOpen, bool drawRoot = true, std::string e = "root");

	//指定の親にノードを追加
	void Add(TreeNode* targetNode, TreeNode* parentNode);

	TreeNode* Delete(std::string e);

	TreeNode* FindNode(std::string e);
	TreeNode* FindNode(std::vector<std::string> pathes);

	void Draw();

	TreeNode* GetRoot();	//ルートを取得

	void UpdateNodes();	//階層を更新

	int UpdateNodeAndChildrenNodes(TreeNode* node, int row);	//nodeとnodeの子を含むノードのrowとstairNoをすべてセットする
private:
	TreeNode* root = nullptr;

	bool drawRoot;

	//文字関連
	//int CreateFontToHandle(char* FontName, int Size, int Thick, int FontType);

};
