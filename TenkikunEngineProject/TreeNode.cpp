#include "TreeNode.h"
#include "SceneManager.h"
#include "Debug.h"

TreeNode::TreeNode(std::string e, TreeList* treeList, bool isOpen) : TriggerRect(treeList->parentWindow->startX + treeList->buttonWidth, treeList->parentWindow->startY, (float)GetDrawStringWidth(e.c_str(), (int)(e.length())), (float)GetFontLineSpace(), treeList->parentWindow)
{
	element = e;
	this->treeList = treeList;
	this->isOpen = isOpen;

	mouseClickDownEvents.push_back([this]() {
		//�N���b�N�����Ƃ��Ɏ��g��I�𒆂ɂ���
		this->parentWindow->SetSelectedTriggerRect(this);
		GameObject* gameobject = GameObject::Find(this->GetElement());	//���̃m�[�h�̖��O���炩��Q�[���I�u�W�F�N�g�擾
		//���������Ȃ�
		if (gameobject) {
			WindowManager::inspectorWindow->SetGameObject(gameobject);	//�Q�[���I�u�W�F�N�g�̏����q�G�����L�[�ɃZ�b�g
		}
	});

	button = new WindowButton(startX - treeList->buttonWidth, startY, treeList->buttonWidth, treeList->buttonWidth, treeList->parentWindow);	//�{�^���쐬
	//�摜�Z�b�g
	button->image = treeList->images[isOpen];

	//�{�^�����N���b�N������
	button->onClickEvents.push_back([this, treeList]() {
		//�J���Ă��邩�̔���𔽓]������
		this->isOpen = !this->isOpen;
		//�摜�Z�b�g
		button->image = treeList->images[this->isOpen];
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
		if (isOn) {
			//�l�p�̕`��
			DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(200, 200, 200), TRUE);
		}
	}
	//�����̕`��(��)
	DrawStringF(startX, startY, element.c_str(), GetColor(0, 0, 0));

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
