#include "TreeNode.h"
#include "SceneManager.h"
#include "Debug.h"
#include "FontManager.h"

TreeNode::TreeNode(std::string e, TreeList* treeList, bool isOpen) : TriggerRect(treeList->startX + FontManager::systemFont->GetFontHeight(), treeList->startY, FontManager::systemFont->GetFontWidth(e), FontManager::systemFont->GetFontHeight(), 1)
{
	element = e;
	this->treeList = treeList;
	this->isOpen = isOpen;

	//クリックした瞬間なら
	mouseClickDownEvents.push_back(std::make_pair(GetEventNo(), [this]() {
		//自身を選択中にする
		WindowManager::SetSelectedTriggerRect(this);
	}));

	mouseRightClickEvents.push_back(std::make_pair(GetEventNo(), [this]() {
		//選択対象にする
		WindowManager::SetSelectedTriggerRect(this);
	}));

	button = new WindowButton(startX - height, startY, height, height, treeList->images[isOpen]);	//ボタン作成

	//ボタンをクリックしたら
	button->onClickEvents.push_back(std::make_pair(button->GetEventNo(), [this, treeList]() {
		//開いているかの判定を反転させる
		this->isOpen = !this->isOpen;
		//画像セット
		button->SetImage(treeList->images[this->isOpen]);
		//ツリーリスト更新
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
	//名前セット
	this->element = element;
	//それによる幅、高さ更新
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

	//ノードがnullになるまで(ルートの親がnullなのでそこまで)
	for (int i = 0; node; i++) {
		//最初以外は
		if (i != 0) {
			//\\を追加
			path = "\\" + path;
		}
		//ノードの名前を追加
		path = node->element + path;
		//ノードの親を参照するようにする
		node = node->parentNode;
	}

	return path;
}

void TreeNode::Draw()
{
	//選択されているなら
	if (GetIsSelected()) {
		//四角の描画
		DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(30, 144, 255), TRUE);
	}
	//選択されていないなら
	else {
		//マウスが乗っていたら
		if (GetIsTopOn()) {
			//四角の描画
			DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(200, 200, 200), TRUE);
		}
	}
	//文字の描画(黒)
	DrawStringFToHandle(startX, startY, element.c_str(), GetColor(0, 0, 0), FontManager::systemFont->GetFH());

	//ボタンの描画
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

		//リストに追加
		nodes.push_back(node);

		//子らを追加
		tmp.insert(tmp.end(), node->childNodes.begin(), node->childNodes.end());
	}

	return nodes;
}

void TreeNode::PreparationLibrate()
{
	//WindowButtonの解放準備
	button->PreparationLibrate();
	//解放
	delete(button);
	button = nullptr;

	//自身の解放準備
	TriggerRect::PreparationLibrate();
}
