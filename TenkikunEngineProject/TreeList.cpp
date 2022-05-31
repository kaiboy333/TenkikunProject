#include "TreeList.h"

TreeList::TreeList(Window* window, bool drawRoot, std::string e)
{
	//root�쐬
	root = new TreeNode("root");
	//window�Z�b�g
	this->window = window;

	this->drawRoot = drawRoot;
}

void TreeList::Add(TreeNode* targetNode, TreeNode* parentNode)
{
	if (!targetNode)
		return;

	//�e���w�肳�ꂽ�Ȃ�
	if (parentNode) {			
		//�e�ɂ���q�̃��X�g��ǉ�
		parentNode->childNodes.push_back(targetNode);
		//�q�ɐe���w��
		targetNode->parentNode = parentNode;
		//�w��̃m�[�h�̊K�w���X�V
		targetNode->UpdateStairNo();
	}
}

TreeNode* TreeList::Delete(std::string e)
{
	TreeNode* node = FindNode(e);
	if (node) {
		//�e�̃m�[�h���烊�X�g���擾
		std::vector<TreeNode*>* childNodes = &node->parentNode->childNodes;
		//�w��̃m�[�h���폜
		childNodes->erase(remove(childNodes->begin(), childNodes->end(), node));
		//�e�̎Q�Ƃ��폜
		node->parentNode = nullptr;
	}
	//�m�[�h��Ԃ�
	return node;
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

			float startX = window->startX + iconWidth * (node->GetStairNo() + 1) + tabSpace * (node->GetStairNo());
			float startY = window->startY + stringHeight * i;

			//�A�C�R���̕`��
			DrawBoxAA(startX - iconWidth, startY, startX - 1, startY + stringHeight - 1, GetColor(0, 0, 0), TRUE);
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

TreeNode* TreeList::GetRoot()
{
	return root;
}
