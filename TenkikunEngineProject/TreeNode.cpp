#include "TreeNode.h"

TreeNode::TreeNode(std::string e, TreeList* treeList) : TriggerRect(treeList->window->startX + iconWidth, treeList->window->startY, (float)GetDrawStringWidth(e.c_str(), (float)((int)e.length())), (float)GetFontLineSpace())
{
	element = e;
	this->treeList = treeList;

	//�N���b�N�����Ƃ��Ɏ��g��I�𒆂ɂ���
	mouseClickEvents.push_back([this]() {
		WindowManager::SetSelectedTriggerRect(this);
		});
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
	width = (float)GetDrawStringWidth(element.c_str(), (int)element.length());
	height = (float)GetFontLineSpace();
}

std::string TreeNode::GetElement()
{
	return element;
}

void TreeNode::Draw()
{
	//�A�C�R���̕`��
	DrawBoxAA(startX - iconWidth, startY, startX - 1, startY + height - 1, GetColor(0, 0, 0), TRUE);
	//�I������Ă���Ȃ�
	if (isSelected) {
		//�l�p�̕`��
		DrawBoxAA(startX, startY, startX + width - 1, startY + height - 1, GetColor(30, 144, 255), TRUE);
	}
	//�I������Ă��Ȃ��Ȃ�
	else {
		//�}�E�X������Ă�����
		if (isOn) {
			//�l�p�̕`��
			DrawBoxAA(startX, startY, startX + width - 1, startY + height - 1, GetColor(200, 200, 200), TRUE);
		}
	}
	//�����̕`��(��)
	DrawStringF(startX, startY, element.c_str(), GetColor(0, 0, 0));
}
