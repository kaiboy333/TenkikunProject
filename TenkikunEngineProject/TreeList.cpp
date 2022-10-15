#include "TreeList.h"
#include "ProjectFileManager.h"
#include "MyString.h"

TreeList::TreeList(float startX, float startY, float width, float height, bool isFirstOpen, bool drawRoot, std::string rootName) : ScrollRect(startX, startY, width, height, width, height)
{
	//�m�[�h�̃{�^���摜��T��
	images[0] = static_cast<Image*>(ProjectFileManager::pathAndInfo[ProjectFileManager::resourceFilePath.string() + "\\RightArrow.png"]);
	images[1] = static_cast<Image*>(ProjectFileManager::pathAndInfo[ProjectFileManager::resourceFilePath.string() + "\\DownArrow.png"]);

	this->drawRoot = drawRoot;

	this->isFirstOpen = isFirstOpen;

	//root�쐬
	root = new TreeNode(rootName, this, isFirstOpen);
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
		//ScrollRect�̃��X�g�ɒǉ�(&�X�V)
		AddToScrollRect(targetNode);
		AddToScrollRect(targetNode->button);	//�{�^����
		//�m�[�h�̊K�w���X�V
		UpdateNodes();
	}
}

void TreeList::Delete(std::string e)
{
	TreeNode* targetNode = FindNode(e);
	if (targetNode) {
		//�e������Ȃ�
		TreeNode* parentNode = targetNode->parentNode;
		if (parentNode) {
			//�e�̃��X�g���玩�g���폜
			parentNode->childNodes.erase(std::remove(parentNode->childNodes.begin(), parentNode->childNodes.end(), targetNode));
		}

		std::vector<TreeNode*> nodes;
		nodes.push_back(targetNode);
		while ((int)nodes.size() != 0) {
			TreeNode* node = nodes[0];
			nodes.erase(nodes.begin());

			//ScrollRect�̃��X�g����폜
			RemoveToScrollRect(node);
			RemoveToScrollRect(node->button);	//�{�^����

			nodes.insert(nodes.end(), node->childNodes.begin(), node->childNodes.end());

			//Node�̏����A���
			node->PreparationLibrate();
			delete(node);
		}

		//root�m�[�h�ł͂Ȃ��Ȃ�
		if (parentNode) {
			//�m�[�h�̊K�w���X�V
			UpdateNodes();
		}
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

		if (node->GetPath() == e)
			return node;

		//�q���ǉ�
		nodes.insert(nodes.end(), node->childNodes.begin(), node->childNodes.end());
	}
	return nullptr;
}

//TreeNode* TreeList::FindNode(std::vector<std::string> pathes)
//{
//	//���X�g�̐擪�̗v�f���擾�A�폜
//	std::vector<TreeNode*> nodes;
//	nodes.push_back(root);
//
//	int i = 0;
//
//	while (nodes.size() != 0) {
//
//		TreeNode* node = nodes[0];
//		nodes.erase(nodes.begin());
//
//		if (node->GetElement() == pathes[i]) {
//			//����string��
//			i++;
//			//�m�[�h���Z�b�g
//			nodes.clear();
//			//�Ō�܂ł��ǂ蒅������(����������)
//			if (pathes.size() == i) {
//				//���������̂�Ԃ�
//				return node;
//			}
//			//�q���ǉ�
//			nodes.insert(nodes.end(), node->childNodes.begin(), node->childNodes.end());
//		}
//	}
//
//	//������Ȃ�������null��Ԃ�
//	return nullptr;
//}

void TreeList::Draw()
{
	RECT beforeDrawRect;
	//�`��̈���L��
	GetDrawArea(&beforeDrawRect);

	//�`��͈͐���
	SetDrawArea((int)startX, (int)startY, (int)(startX + width), (int)(startY + height));

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
	DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(0, 0, 0), FALSE);

	//�O��̕`��̈�ɖ߂�
	SetDrawArea(beforeDrawRect.left, beforeDrawRect.top, beforeDrawRect.right, beforeDrawRect.bottom);
}

void TreeList::SetRoot(TreeNode*)
{
}

TreeNode* TreeList::GetRoot()
{
	return root;
}

void TreeList::UpdateNodes()
{
	//�X�N���[���̍����̓m�[�h�̐��ƃm�[�h�̍������|������
	scrollHeight = UpdateNodeAndChildrenNodes(root, 0) * root->height;
	
	ScrollUpdate();	//�L�����X�V
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
	node->startX = startX + tabSpace * (node->GetStairNo() + 1) + node->button->width * node->GetStairNo() + (startScrollX - startX);
	node->startY = startY + node->GetRow() * node->height + (startScrollY - startY);

	node->button->startX = node->startX - node->button->width;
	node->button->startY = node->startY;
	//�q�m�[�h�����Ȃ��Ȃ�{�^���𖳌���
	node->button->isActive = ((int)node->childNodes.size() != 0);

	for (TreeNode* childNode : node->childNodes) {
		row = UpdateNodeAndChildrenNodes(childNode, row);
	}

	return row;
}

void TreeList::PreparationLibrate()
{
	//�m�[�h�����ׂĉ��
	Delete(GetRoot()->GetPath());

	//���g�̉������
	ScrollRect::PreparationLibrate();
}
