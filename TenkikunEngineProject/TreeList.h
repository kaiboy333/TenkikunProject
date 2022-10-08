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
	//�{�^���摜(�J���Ă��Ȃ��̂ƊJ���Ă���Ƃ�)
	Image* images[2];

	//�e����q�̗]��
	float tabSpace = 12;

	bool isFirstOpen;	//�m�[�h�ǉ����ɊJ������ԂŒǉ����邩

	TreeList(float startX, float startY, float width, float height, bool isFirstOpen, bool drawRoot = true, std::string e = "root");

	//�w��̐e�Ƀm�[�h��ǉ�
	void Add(TreeNode* targetNode, TreeNode* parentNode);

	TreeNode* Delete(std::string e);

	TreeNode* FindNode(std::string e);
	TreeNode* FindNode(std::vector<std::string> pathes);

	void Draw();

	TreeNode* GetRoot();	//���[�g���擾

	void UpdateNodes();	//�K�w���X�V

	int UpdateNodeAndChildrenNodes(TreeNode* node, int row);	//node��node�̎q���܂ރm�[�h��row��stairNo�����ׂăZ�b�g����
private:
	TreeNode* root = nullptr;

	bool drawRoot;

	//�����֘A
	//int CreateFontToHandle(char* FontName, int Size, int Thick, int FontType);

};
