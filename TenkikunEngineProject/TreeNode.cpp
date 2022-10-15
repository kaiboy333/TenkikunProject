#include "TreeNode.h"
#include "SceneManager.h"
#include "Debug.h"
#include "FontManager.h"

TreeNode::TreeNode(std::string e, TreeList* treeList, bool isOpen) : TriggerRect(treeList->startX + FontManager::systemFont->GetFontHeight(), treeList->startY, FontManager::systemFont->GetFontWidth(e), FontManager::systemFont->GetFontHeight(), 1)
{
	element = e;
	this->treeList = treeList;
	this->isOpen = isOpen;

	//�N���b�N�����u�ԂȂ�
	mouseClickDownEvents.push_back(std::make_pair(GetEventNo(), [this]() {
		//���g��I�𒆂ɂ���
		WindowManager::SetSelectedTriggerRect(this);
	}));

	mouseRightClickEvents.push_back(std::make_pair(GetEventNo(), [this]() {
		//�I��Ώۂɂ���
		WindowManager::SetSelectedTriggerRect(this);
	}));

	button = new WindowButton(startX - height, startY, height, height, treeList->images[isOpen]);	//�{�^���쐬

	//�{�^�����N���b�N������
	button->onClickEvents.push_back(std::make_pair(button->GetEventNo(), [this, treeList]() {
		//�J���Ă��邩�̔���𔽓]������
		this->isOpen = !this->isOpen;
		//�摜�Z�b�g
		button->SetImage(treeList->images[this->isOpen]);
		//�c���[���X�g�X�V
		treeList->UpdateNodes();
	}));
}

int TreeNode::GetStairNo()
{
	return stairNo;
}

void TreeNode::SetStairNo(int stairNo)
{
	this->stairNo = stairNo;
}

int TreeNode::GetRow()
{
	return row;
}

void TreeNode::SetRow(int row)
{
	this->row = row;
}

void TreeNode::SetElement(std::string element)
{
	//���O�Z�b�g
	this->element = element;
	//����ɂ�镝�A�����X�V
	width = FontManager::systemFont->GetFontWidth(element);
	height = FontManager::systemFont->GetFontHeight();
	if (activeRect) {
		activeRect->width = FontManager::systemFont->GetFontWidth(element);
		activeRect->height = FontManager::systemFont->GetFontHeight();
	}
}

std::string TreeNode::GetElement()
{
	return element;
}

string TreeNode::GetPath()
{
	TreeNode* node = this;
	string path = "";

	//�m�[�h��null�ɂȂ�܂�(���[�g�̐e��null�Ȃ̂ł����܂�)
	for (int i = 0; node; i++) {
		//�ŏ��ȊO��
		if (i != 0) {
			//\\��ǉ�
			path = "\\" + path;
		}
		//�m�[�h�̖��O��ǉ�
		path = node->element + path;
		//�m�[�h�̐e���Q�Ƃ���悤�ɂ���
		node = node->parentNode;
	}

	return path;
}

void TreeNode::Draw()
{
	//�I������Ă���Ȃ�
	if (GetIsSelected()) {
		//�l�p�̕`��
		DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(30, 144, 255), TRUE);
	}
	//�I������Ă��Ȃ��Ȃ�
	else {
		//�}�E�X������Ă�����
		if (GetIsTopOn()) {
			//�l�p�̕`��
			DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(200, 200, 200), TRUE);
		}
	}
	//�����̕`��(��)
	DrawStringFToHandle(startX, startY, element.c_str(), GetColor(0, 0, 0), FontManager::systemFont->GetFH());

	//�{�^���̕`��
	button->Draw();
}

vector<TreeNode*> TreeNode::GetAllLowStairChildren()
{
	std::vector<TreeNode*> nodes;

	std::vector<TreeNode*> tmp;
	tmp.push_back(this);

	while (tmp.size() != 0) {

		TreeNode* node = tmp[0];
		tmp.erase(tmp.begin());

		//���X�g�ɒǉ�
		nodes.push_back(node);

		//�q���ǉ�
		tmp.insert(tmp.end(), node->childNodes.begin(), node->childNodes.end());
	}

	return nodes;
}

void TreeNode::PreparationLibrate()
{
	//WindowButton�̉������
	button->PreparationLibrate();
	//���
	delete(button);
	button = nullptr;

	//���g�̉������
	TriggerRect::PreparationLibrate();
}
