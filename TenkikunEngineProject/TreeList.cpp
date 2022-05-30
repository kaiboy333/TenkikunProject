#include "TreeList.h"

TreeList::TreeList(Window* window, bool drawRoot, std::string e)
{
	//root作成
	root = new TreeNode("root");
	//windowセット
	this->window = window;

	this->drawRoot = drawRoot;
}

void TreeList::Add(std::string e, TreeNode* parentNode)
{
	//親が指定されたなら
	if (parentNode) {
		//ノードを作成
		TreeNode* node = new TreeNode(e, parentNode->stairNo + 1);
		//親にある子のリストを追加
		parentNode->childNodes.push_back(node);
		//子に親を指定
		node->parentNode = parentNode;
	}
}

void TreeList::Delete(std::string e)
{
	TreeNode* node = FindNode(e);
	if (node) {
		//親のノードからリストを取得
		std::vector<TreeNode*> childNodes = node->parentNode->childNodes;
		//指定のノードを削除
		childNodes.erase(remove(childNodes.begin(), childNodes.end(), node));
	}
}

TreeNode* TreeList::FindNode(std::string e)
{
	std::vector<TreeNode*> nodes;
	nodes.push_back(root);

	while (nodes.size() != 0) {

		//リストの先頭の要素を取得、削除
		TreeNode* node = nodes[0];
		nodes.erase(nodes.begin());

		if (node->element == e)
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
		int i = 0;

		//リストの先頭の要素を取得、削除
		std::vector<TreeNode*> nodes;
		nodes.push_back(root);

		while (nodes.size() != 0) {

			TreeNode* node = nodes[0];
			nodes.erase(nodes.begin());

			//文字の幅取得
			float stringWidth = GetDrawStringWidth(node->element.c_str(), node->element.length());
			//文字の高さ取得
			float stringHeight = GetFontLineSpace();

			float startX = window->startX + iconWidth * (node->stairNo + 1) + tabSpace * (node->stairNo);
			float startY = window->startY + stringHeight * i;

			//四角の描画
			DrawBoxAA(startX, startY, startX + stringWidth - 1, startY + stringHeight - 1, GetColor(0, 0, 0), FALSE);
			//文字の描画(黒)
			DrawStringF(startX, startY, node->element.c_str(), GetColor(0, 0, 0));
			//次へ
			i++;

			//開いている状態なら
			if (node->isOpen) {
				//子らを追加
				nodes.insert(nodes.end(), node->childNodes.begin(), node->childNodes.end());
			}

		}
	}
}