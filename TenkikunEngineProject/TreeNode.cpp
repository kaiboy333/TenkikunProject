#include "TreeNode.h"

TreeNode::TreeNode(std::string e, TreeList* treeList) : TriggerRect(treeList->window->startX + iconWidth, treeList->window->startY, (float)GetDrawStringWidth(e.c_str(), (float)((int)e.length())), (float)GetFontLineSpace())
{
	element = e;
	this->treeList = treeList;

	//クリックしたときに自身を選択中にする
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
	//名前セット
	this->element = element;
	//それによる幅、高さ更新
	width = (float)GetDrawStringWidth(element.c_str(), (int)element.length());
	height = (float)GetFontLineSpace();
}

std::string TreeNode::GetElement()
{
	return element;
}

void TreeNode::Draw()
{
	//アイコンの描画
	DrawBoxAA(startX - iconWidth, startY, startX - 1, startY + height - 1, GetColor(0, 0, 0), TRUE);
	//選択されているなら
	if (isSelected) {
		//四角の描画
		DrawBoxAA(startX, startY, startX + width - 1, startY + height - 1, GetColor(30, 144, 255), TRUE);
	}
	//選択されていないなら
	else {
		//マウスが乗っていたら
		if (isOn) {
			//四角の描画
			DrawBoxAA(startX, startY, startX + width - 1, startY + height - 1, GetColor(200, 200, 200), TRUE);
		}
	}
	//文字の描画(黒)
	DrawStringF(startX, startY, element.c_str(), GetColor(0, 0, 0));
}
