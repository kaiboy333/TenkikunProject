#include "TreeNode.h"
#include "SceneManager.h"
#include "Debug.h"

TreeNode::TreeNode(std::string e, TreeList* treeList, bool isOpen) : TriggerRect(treeList->parentWindow->startX + treeList->buttonWidth, treeList->parentWindow->startY, (float)GetDrawStringWidth(e.c_str(), (int)(e.length())), (float)GetFontLineSpace(), treeList->parentWindow)
{
	element = e;
	this->treeList = treeList;
	this->isOpen = isOpen;

	mouseClickDownEvents.push_back([this]() {
		//クリックしたときに自身を選択中にする
		this->parentWindow->SetSelectedTriggerRect(this);
		GameObject* gameobject = GameObject::Find(this->GetElement());	//このノードの名前からからゲームオブジェクト取得
		//見つかったなら
		if (gameobject) {
			WindowManager::inspectorWindow->SetGameObject(gameobject);	//ゲームオブジェクトの情報をヒエラルキーにセット
		}
	});

	button = new WindowButton(startX - treeList->buttonWidth, startY, treeList->buttonWidth, treeList->buttonWidth, treeList->parentWindow);	//ボタン作成
	//画像セット
	button->image = treeList->images[isOpen];

	//ボタンをクリックしたら
	button->onClickEvents.push_back([this, treeList]() {
		//開いているかの判定を反転させる
		this->isOpen = !this->isOpen;
		//画像セット
		button->image = treeList->images[this->isOpen];
		//ツリーリスト更新
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
		if (isOn) {
			//四角の描画
			DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(200, 200, 200), TRUE);
		}
	}
	//文字の描画(黒)
	DrawStringF(startX, startY, element.c_str(), GetColor(0, 0, 0));

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
