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

	//�w��̐e�Ƀm�[�h��ǉ�
	void Add(std::string e, TreeNode* parentNode);
	void Delete(std::string e);

	TreeNode* FindNode(std::string e);

	Window* window = nullptr;

	void Draw();


private:
	TreeNode* root = nullptr;

	//�e����q�̗]��
	float tabSpace = 5;

	//�A�C�R���̕�
	float iconWidth = 5;

	bool drawRoot;

	//�����֘A
	//int CreateFontToHandle(char* FontName, int Size, int Thick, int FontType);

};
