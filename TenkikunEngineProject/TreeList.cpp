#include "TreeList.h"

TreeList::TreeList(float startX, float startY, float width, float height, Window* parentWindow, bool isFirstOpen, bool drawRoot, std::string e) : ScrollRect(startX, startY, width, height, width, height, parentWindow)
{
	//�m�[�h�̃{�^���摜�Z�b�g
	images[0] = new Image("image/rightArrow.png");
	images[1] = new Image("image/downArrow.png");

	this->drawRoot = drawRoot;

	this->isFirstOpen = isFirstOpen;

	//root�쐬
	root = new TreeNode(e, this, isFirstOpen);
	//�m�[�h�̊K�w���X�V
	UpdateNodes();
	//ScrollRect�̃��X�g�ɒǉ�(&�X�V)
	AddToScrollRect(root);
	AddToScrollRect(root->button);	//�{�^����
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
		//ScrollRect�̃��X�g�ɒǉ�(&�X�V)
		AddToScrollRect(targetNode);
		AddToScrollRect(targetNode->button);	//�{�^����
	}
}

TreeNode* TreeList::Delete(std::string e)
{
	TreeNode* targetNode = FindNode(e);
	if (targetNode) {
		//�e�̃m�[�h���烊�X�g���擾
		std::vector<TreeNode*>* childNodes = &targetNode->parentNode->childNodes;
		//�w��̃m�[�h���폜
		childNodes->erase(remove(childNodes->begin(), childNodes->end(), targetNode));
		//�e�̎Q�Ƃ��폜
		targetNode->parentNode = nullptr;
		//ScrollRect�̃��X�g����폜
		RemoveToScrollRect(targetNode);
		RemoveToScrollRect(targetNode->button);	//�{�^����
		//�m�[�h�̊K�w���X�V
		UpdateNodes();
	}
	//�m�[�h��Ԃ�
	return targetNode;
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
	if (this->parentWindow) {
		//����ڂ̕`�悩
		//int i = 0;

		//���X�g�̐擪�̗v�f���擾�A�폜
		std::vector<TreeNode*> nodes;
		nodes.push_back(root);

		while (nodes.size() != 0) {

			TreeNode* node = nodes[0];
			nodes.erase(nodes.begin());

			if (node->isActive) {
				node->Draw();
			}

			//�q���ǉ�
			nodes.insert(nodes.end(), node->childNodes.begin(), node->childNodes.end());
		}
	}
}

TreeNode* TreeList::GetRoot()
{
	return root;
}

void TreeList::UpdateNodes()
{
	//�X�N���[���̍����̓m�[�h�̐��ƃm�[�h�̍������|������
	scrollHeight = UpdateNodeAndChildrenNodes(root, 0) * root->height;
}

int TreeList::UpdateNodeAndChildrenNodes(TreeNode* node, int row)
{
	//�e�m�[�h������Ȃ�
	if (node->parentNode) {
		//�e������������Ă���̂Ȃ�
		if (!node->parentNode->isActive) {
			//���g�𖳌���
			node->isActive = false;
		}
		//�e���L��������Ă���̂Ȃ�
		else {
			//�e�̃m�[�h���J���Ă����ԂŗL�������܂�
			node->isActive = node->parentNode->isOpen;
		}
	}

	node->SetRow(node->isActive ? row++ : row);
	node->SetStairNo(node->parentNode ? node->parentNode->GetStairNo() + 1 : 0);

	//�J�n�ʒu�Z�b�g
	node->startX = parentWindow->startX + tabSpace * (node->GetStairNo() + 1) + buttonWidth * node->GetStairNo() - (startScrollX - startX);
	node->startY = parentWindow->startY + node->GetRow() * node->height - (startScrollY - startY);

	node->button->startX = node->startX - buttonWidth;
	node->button->startY = node->startY;
	//�q�m�[�h�����Ȃ��Ȃ�{�^���𖳌���
	node->button->isActive = ((int)node->childNodes.size() != 0);

	for (TreeNode* childNode : node->childNodes) {
		row = UpdateNodeAndChildrenNodes(childNode, row);
	}

	return row;
}
