#include "TreeList.h"

TreeList::TreeList(Window* window, bool drawRoot, std::string e)
{
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

			////文字の幅取得
			//float stringWidth = GetDrawStringWidth(node->element.c_str(), node->element.length());
			////文字の高さ取得
			//float stringHeight = GetFontLineSpace();

			//float startX = window->startX + iconWidth * (node->GetStairNo() + 1) + tabSpace * (node->GetStairNo());
			//float startY = window->startY + stringHeight * i;

			////アイコンの描画
			//DrawBoxAA(startX - iconWidth, startY, startX - 1, startY + stringHeight - 1, GetColor(0, 0, 0), TRUE);
			////四角の描画
			//DrawBoxAA(startX, startY, startX + stringWidth - 1, startY + stringHeight - 1, GetColor(0, 0, 0), FALSE);
			////文字の描画(黒)
			//DrawStringF(startX, startY, node->element.c_str(), GetColor(0, 0, 0));
			//次へ
			//i++;

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
		node->startX = window->startX + node->tabSpace * (node->GetStairNo() + 1) + node->iconWidth * node->GetStairNo();
		node->startY = window->startY + node->GetRow() * node->height;
		i++;

		//子らを追加
		nodes.insert(nodes.end(), node->childNodes.begin(), node->childNodes.end());
	}
}
