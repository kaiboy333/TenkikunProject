#include "TreeList.h"

TreeList::TreeList(Window* window, bool drawRoot, std::string e)
{
	//�m�[�h�̃{�^���摜�Z�b�g
	images[0] = new Image("image/rightArrow.png");
	images[1] = new Image("image/downArrow.png");

	//window�Z�b�g
	this->window = window;
	this->drawRoot = drawRoot;

	//root�쐬
	root = new TreeNode(e, this);
	//�m�[�h�̊K�w���X�V
	UpdateNodes();
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
		//�m�[�h�̊K�w���X�V
		UpdateNodes();
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
		//�m�[�h�̊K�w���X�V
		UpdateNodes();
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

		if (node->GetElement() == e)
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
		//int i = 0;

		//���X�g�̐擪�̗v�f���擾�A�폜
		std::vector<TreeNode*> nodes;
		nodes.push_back(root);

		while (nodes.size() != 0) {

			TreeNode* node = nodes[0];
			nodes.erase(nodes.begin());

			node->Draw();

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

void TreeList::UpdateNodes()
{
	std::vector<TreeNode*> nodes;
	nodes.push_back(root);

	int i = 0;

	while (nodes.size() != 0) {

		//���X�g�̐擪�̗v�f���擾�A�폜
		TreeNode* node = nodes[0];
		nodes.erase(nodes.begin());

		//�K�w���Z�b�g
		node->SetStairNo(node->parentNode ? node->parentNode->GetStairNo() + 1 : 0);
		//�s�����Z�b�g
		node->SetRow(i);
		//�J�n�ʒu�Z�b�g
		node->startX = window->startX + tabSpace * (node->GetStairNo() + 1) + buttonWidth * node->GetStairNo();
		node->startY = window->startY + node->GetRow() * node->height;

		node->button->startX = node->startX - buttonWidth;
		node->button->startY = node->startY;
		//�q�m�[�h�����Ȃ��Ȃ�{�^���𖳌���
		node->button->isActive = ((int)node->childNodes.size() != 0);
		i++;

		//�q���ǉ�
		nodes.insert(nodes.end(), node->childNodes.begin(), node->childNodes.end());
	}
}
