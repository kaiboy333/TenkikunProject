#pragma once

#include "SceneManager.h"
#include "WindowManager.h"
#include "Window.h"
#include <iostream>
#include <vector>
#include <string>
#include "Property.h"
#include "TreeNode.h"

class TreeNode;
class TreeList
{
public:
	//ボタン画像(開いていないのと開いているとき)
	Image* images[2];

	//親から子の余白
	float tabSpace = 18;

	//ボタン画像の幅
	float buttonWidth = 18;

	TreeList(Window* window, bool drawRoot = true, std::string e = "root");

	//指定の親にノードを追加
	void Add(TreeNode* targetNode, TreeNode* parentNode);

	TreeNode* Delete(std::string e);

	TreeNode* FindNode(std::string e);

	Window* window = nullptr;

	void Draw();

	TreeNode* GetRoot();	//ルートを取得

	void UpdateNodes();	//階層を更新

private:
	TreeNode* root = nullptr;

	bool drawRoot;

	//文字関連
	//int CreateFontToHandle(char* FontName, int Size, int Thick, int FontType);

};
