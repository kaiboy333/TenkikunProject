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
	//�{�^���摜(�J���Ă��Ȃ��̂ƊJ���Ă���Ƃ�)
	Image* images[2];

	//�e����q�̗]��
	float tabSpace = 18;

	//�{�^���摜�̕�
	float buttonWidth = 18;

	TreeList(Window* window, bool drawRoot = true, std::string e = "root");

	//�w��̐e�Ƀm�[�h��ǉ�
	void Add(TreeNode* targetNode, TreeNode* parentNode);

	TreeNode* Delete(std::string e);

	TreeNode* FindNode(std::string e);

	Window* window = nullptr;

	void Draw();

	TreeNode* GetRoot();	//���[�g���擾

	void UpdateNodes();	//�K�w���X�V

private:
	TreeNode* root = nullptr;

	bool drawRoot;

	//�����֘A
	//int CreateFontToHandle(char* FontName, int Size, int Thick, int FontType);

};
