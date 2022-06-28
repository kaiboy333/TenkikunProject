#include "TreeNode.h"
#include "SceneManager.h"

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

vector<string> TreeNode::GetPathes()
{
	TreeNode* node = this;
	vector<string> pathes;

	//ノードがnullになるまで(ルートの親がnullなのでそこまで)
	while (node) {
		//ノードの名前を追加
		pathes.insert(pathes.begin(), node->element);
	}

	return pathes;
}

void TreeNode::Draw()
{
	//選択されているなら
	if (GetIsSelected()) {
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

	//ボタンの描画
	button->Draw();
}
