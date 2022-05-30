#include "TreeList.h"

TreeList::TreeList(Window* window, bool drawRoot, std::string e)
{
	//root�쐬
	root = new TreeNode("root");
	//window�Z�b�g
	this->window = window;

	this->drawRoot = drawRoot;
}

void TreeList::Add(std::string e, TreeNode* parentNode)
{
	//�e���w�肳�ꂽ�Ȃ�
	if (parentNode) {
		//�m�[�h���쐬
		TreeNode* node = new TreeNode(e, parentNode->stairNo + 1);
		//�e�ɂ���q�̃��X�g��ǉ�
		parentNode->childNodes.push_back(node);
		//�q�ɐe���w��
		node->parentNode = parentNode;
	}
}

void TreeList::Delete(std::string e)
{
	TreeNode* node = FindNode(e);
	if (node) {
		//�e�̃m�[�h���烊�X�g���擾
		std::vector<TreeNode*> childNodes = node->parentNode->childNodes;
		//�w��̃m�[�h���폜
		childNodes.erase(remove(childNodes.begin(), childNodes.end(), node));
	}
}

TreeNode* TreeList::FindNode(std::string e)
{
	std::vector<TreeNode*> nodes;
	nodes.push_back(root);

	while (nodes.size() != 0) {

		//���X�g�̐擪�̗v�f���擾�A�폜
		TreeNode* node = nodes[0];
		nodes.erase(nodes.begin());

		if (node->element == e)
			return node;

		//�q���ǉ�
		nodes.insert(nodes.end(), node->childNodes.begin(), node->childNodes.end());
	}
	return nullptr;
}

void TreeList::Draw()
{
	if (this->window) {
		//����ڂ̕`�悩
		int i = 0;

		//���X�g�̐擪�̗v�f���擾�A�폜
		std::vector<TreeNode*> nodes;
		nodes.push_back(root);

		while (nodes.size() != 0) {

			TreeNode* node = nodes[0];
			nodes.erase(nodes.begin());

			//�����̕��擾
			float stringWidth = GetDrawStringWidth(node->element.c_str(), node->element.length());
			//�����̍����擾
			float stringHeight = GetFontLineSpace();

			float startX = window->startX + iconWidth * (node->stairNo + 1) + tabSpace * (node->stairNo);
			float startY = window->startY + stringHeight * i;

			//�l�p�̕`��
			DrawBoxAA(startX, startY, startX + stringWidth - 1, startY + stringHeight - 1, GetColor(0, 0, 0), FALSE);
			//�����̕`��(��)
			DrawStringF(startX, startY, node->element.c_str(), GetColor(0, 0, 0));
			//����
			i++;

			//�J���Ă����ԂȂ�
			if (node->isOpen) {
				//�q���ǉ�
				nodes.insert(nodes.end(), node->childNodes.begin(), node->childNodes.end());
			}

		}
	}
}