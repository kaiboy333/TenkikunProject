#include "TreeList.h"

TreeList::TreeList(float startX, float startY, float width, float height, Window* parentWindow, bool isFirstOpen, bool drawRoot, std::string e) : ScrollRect(startX, startY, width, height, width, height, parentWindow)
{
	//ノードのボタン画像セット
	images[0] = new Image("image/rightArrow.png");
	images[1] = new Image("image/downArrow.png");

	this->drawRoot = drawRoot;

	this->isFirstOpen = isFirstOpen;

	//root作成
	root = new TreeNode(e, this, isFirstOpen);
	//ノードの階層を更新
	UpdateNodes();
	//ScrollRectのリストに追加(&更新)
	AddToScrollRect(root);
	AddToScrollRect(root->button);	//ボタンも
}

void TreeList::Add(TreeNode* targetNode, TreeNode* parentNode)
{
	if (!targetNode)
		return;

	//親が指定されたなら
	if (parentNode) {			
		//親にある子のリストを追加
		parentNode->childNodes.push_back(targetNode);
		//子に親を指定
		targetNode->parentNode = parentNode;
		//ノードの階層を更新
		UpdateNodes();
		//ScrollRectのリストに追加(&更新)
		AddToScrollRect(targetNode);
		AddToScrollRect(targetNode->button);	//ボタンも
	}
}

TreeNode* TreeList::Delete(std::string e)
{
	TreeNode* targetNode = FindNode(e);
	if (targetNode) {
		//親のノードからリストを取得
		std::vector<TreeNode*>* childNodes = &targetNode->parentNode->childNodes;
		//指定のノードを削除
		childNodes->erase(remove(childNodes->begin(), childNodes->end(), targetNode));
		//親の参照を削除
		targetNode->parentNode = nullptr;
		//ScrollRectのリストから削除
		RemoveToScrollRect(targetNode);
		RemoveToScrollRect(targetNode->button);	//ボタンも
		//ノードの階層を更新
		UpdateNodes();
	}
	//ノードを返す
	return targetNode;
}

TreeNode* TreeList::FindNode(std::string e)
{
	std::vector<TreeNode*> nodes;
	nodes.push_back(root);

	while (nodes.size() != 0) {

		//リストの先頭の要素を取得、削除
		TreeNode* node = nodes[0];
		nodes.erase(nodes.begin());

		if (node->GetElement() == e)
			return node;

		//子らを追加
		nodes.insert(nodes.end(), node->childNodes.begin(), node->childNodes.end());
	}
	return nullptr;
}

void TreeList::Draw()
{
	if (this->parentWindow) {
		//何列目の描画か
		//int i = 0;

		//リストの先頭の要素を取得、削除
		std::vector<TreeNode*> nodes;
		nodes.push_back(root);

		while (nodes.size() != 0) {

			TreeNode* node = nodes[0];
			nodes.erase(nodes.begin());

			if (node->isActive) {
				node->Draw();
			}

			//子らを追加
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
	//スクロールの高さはノードの数とノードの高さを掛けた数
	scrollHeight = UpdateNodeAndChildrenNodes(root, 0) * root->height;
}

int TreeList::UpdateNodeAndChildrenNodes(TreeNode* node, int row)
{
	//親ノードがいるなら
	if (node->parentNode) {
		//親が無効化されているのなら
		if (!node->parentNode->isActive) {
			//自身を無効化
			node->isActive = false;
		}
		//親が有効化されているのなら
		else {
			//親のノードが開いている状態で有効か決まる
			node->isActive = node->parentNode->isOpen;
		}
	}

	node->SetRow(node->isActive ? row++ : row);
	node->SetStairNo(node->parentNode ? node->parentNode->GetStairNo() + 1 : 0);

	//開始位置セット
	node->startX = parentWindow->startX + tabSpace * (node->GetStairNo() + 1) + buttonWidth * node->GetStairNo() - (startScrollX - startX);
	node->startY = parentWindow->startY + node->GetRow() * node->height - (startScrollY - startY);

	node->button->startX = node->startX - buttonWidth;
	node->button->startY = node->startY;
	//子ノードがいないならボタンを無効化
	node->button->isActive = ((int)node->childNodes.size() != 0);

	for (TreeNode* childNode : node->childNodes) {
		row = UpdateNodeAndChildrenNodes(childNode, row);
	}

	return row;
}
