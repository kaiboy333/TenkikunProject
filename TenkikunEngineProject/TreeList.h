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

	TreeList(Window* window, bool drawRoot = true, std::string e = "root");

	//指定の親にノードを追加
	void Add(TreeNode* targetNode, TreeNode* parentNode);

	TreeNode* Delete(std::string e);

	TreeNode* FindNode(std::string e);

	Window* window = nullptr;

	void Draw();

	TreeNode* GetRoot();	//ルートを取得

private:
	TreeNode* root = nullptr;

	//親から子の余白
	float tabSpace = 18;

	//アイコンの幅
	float iconWidth = 18;

	bool drawRoot;

	//文字関連
	//int CreateFontToHandle(char* FontName, int Size, int Thick, int FontType);

};
