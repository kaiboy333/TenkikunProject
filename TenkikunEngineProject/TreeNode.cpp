#include "TreeNode.h"
#include "SceneManager.h"

TreeNode::TreeNode(std::string e, TreeList* treeList) : TriggerRect(treeList->window->startX + treeList->buttonWidth, treeList->window->startY, (float)GetDrawStringWidth(e.c_str(), (int)(e.length())), (float)GetFontLineSpace())
{
	element = e;
	this->treeList = treeList;

	mouseClickDownEvents.push_back([this]() {
		//�N���b�N�����Ƃ��Ɏ��g��I�𒆂ɂ���
		this->parentWindow->SetSelectedTriggerRect(this);
		GameObject* gameobject = GameObject::Find(this->GetElement());	//���̃m�[�h�̖��O���炩��Q�[���I�u�W�F�N�g�擾
		//���������Ȃ�
		if (gameobject) {
			WindowManager::inspectorWindow->SetGameObject(gameobject);	//�Q�[���I�u�W�F�N�g�̏����q�G�����L�[�ɃZ�b�g
		}
	});

	button = new WindowButton(startX - treeList->buttonWidth, startY, treeList->buttonWidth, treeList->buttonWidth);	//�{�^���쐬
	//�摜�Z�b�g
	button->image = treeList->images[isOpen];

	//�{�^�����N���b�N������
	button->onClickEvents.push_back([this, treeList]() {
		//�J���Ă��邩�̔���𔽓]������
		isOpen = !isOpen;
		//�摜�Z�b�g
		button->image = treeList->images[isOpen];
		//�c���[���X�g�X�V
		treeList->UpdateNodes();
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
	//�I������Ă���Ȃ�
	if (GetIsSelected()) {
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

	//�{�^���̕`��
	button->Draw();
}