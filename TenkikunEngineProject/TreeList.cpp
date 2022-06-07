#include "TreeList.h"

TreeList::TreeList(Window* window, bool drawRoot, std::string e)
{
	//ノードのボタン画像セット
	images[0] = new Image("image/rightArrow.png");
	images[1] = new Image("image/downArrow.png");

	//windowセット
	this->window = window;
	this->drawRoot = drawRoot;

	//root作成
	root = new TreeNode(e, this);
	//ノードの階層を更新
	UpdateNodes();
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
	}
}

TreeNode* TreeList::Delete(std::string e)
{
	TreeNode* node = FindNode(e);
	if (node) {
		//親のノードからリストを取得
		std::vector<TreeNode*>* childNodes = &node->parentNode->childNodes;
		//指定のノードを削除
		childNodes->erase(remove(childNodes->begin(), childNodes->end(), node));
		//親の参照を削除
		node->parentNode = nullptr;
		//ノードの階層を更新
		UpdateNodes();
	}
	//ノードを返す
	return node;
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
	if (this->window) {
		//何列目の描画か
		//int i = 0;

		//リストの先頭の要素を取得、削除
		std::vector<TreeNode*> nodes;
		nodes.push_back(root);

		while (nodes.size() != 0) {

			TreeNode* node = nodes[0];
			nodes.erase(nodes.begin());

			node->Draw();

			//開いている状態なら
			if (node->isOpen) {
				//子らを追加
				nodes.insert(nodes.end(), node->childNodes.begin(), node->childNodes.end());
			}

		}
	}
}

TreeNode* TreeList::GetRoot()
{
	return root;
}

void TreeList::UpdateNodes()
{
	std::vector<TreeNode*> nodes;
	nodes.push_back(root);

	int i = 0;

	while (nodes.size() != 0) {

		//リストの先頭の要素を取得、削除
		TreeNode* node = nodes[0];
		nodes.erase(nodes.begin());

		//階層をセット
		node->SetStairNo(node->parentNode ? node->parentNode->GetStairNo() + 1 : 0);
		//行数をセット
		node->SetRow(i);
		//開始位置セット
		node->startX = window->startX + tabSpace * (node->GetStairNo() + 1) + buttonWidth * node->GetStairNo();
		node->startY = window->startY + node->GetRow() * node->height;

		node->button->startX = node->startX - buttonWidth;
		node->button->startY = node->startY;
		//子ノードがいないならボタンを無効化
		node->button->isActive = ((int)node->childNodes.size() != 0);
		i++;

		//子らを追加
		nodes.insert(nodes.end(), node->childNodes.begin(), node->childNodes.end());
	}
}
