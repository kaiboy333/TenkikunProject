#include "TreeList.h"
#include "ProjectFileManager.h"

TreeList::TreeList(float startX, float startY, float width, float height, Window* parentWindow, bool isFirstOpen, bool drawRoot, std::string e) : ScrollRect(startX, startY, width, height, width, height, parentWindow)
{
	//ノードのボタン画像を探す
	images[0] = static_cast<Image*>(ProjectFileManager::pathAndInfo[ProjectFileManager::resourceFilePath.string() + "\\RightArrow.png"]);
	images[1] = static_cast<Image*>(ProjectFileManager::pathAndInfo[ProjectFileManager::resourceFilePath.string() + "\\DownArrow.png"]);

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
		//ScrollRectのリストに追加(&更新)
		AddToScrollRect(targetNode);
		AddToScrollRect(targetNode->button);	//ボタンも
		//ノードの階層を更新
		UpdateNodes();
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

TreeNode* TreeList::FindNode(std::vector<std::string> pathes)
{
	//リストの先頭の要素を取得、削除
	std::vector<TreeNode*> nodes;
	nodes.push_back(root);

	int i = 0;

	while (nodes.size() != 0) {

		TreeNode* node = nodes[0];
		nodes.erase(nodes.begin());

		if (node->GetElement() == pathes[i]) {
			//次のstringへ
			i++;
			//ノードリセット
			nodes.clear();
			//最後までたどり着いたら(見つかったら)
			if (pathes.size() == i) {
				//見つかったのを返す
				return node;
			}
			//子らを追加
			nodes.insert(nodes.end(), node->childNodes.begin(), node->childNodes.end());
		}
	}

	//見つからなかったらnullを返す
	return nullptr;
}

void TreeList::Draw()
{
	RECT beforeDrawRect;
	//描画領域を記憶
	GetDrawArea(&beforeDrawRect);

	//描画範囲制限
	SetDrawArea((int)startX, (int)startY, (int)(startX + width), (int)(startY + height));

	if (this->parentWindow) {
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
	//画像のアルファ値設定
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

	DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(0, 0, 0), FALSE);

	//前回の描画領域に戻す
	SetDrawArea(beforeDrawRect.left, beforeDrawRect.top, beforeDrawRect.right, beforeDrawRect.bottom);
}

TreeNode* TreeList::GetRoot()
{
	return root;
}

void TreeList::UpdateNodes()
{
	//スクロールの高さはノードの数とノードの高さを掛けた数
	scrollHeight = UpdateNodeAndChildrenNodes(root, 0) * root->height;
	
	ScrollUpdate();	//有効化更新
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
	node->startX = parentWindow->startX + tabSpace * (node->GetStairNo() + 1) + node->button->width * node->GetStairNo() + (startScrollX - startX);
	node->startY = parentWindow->startY + node->GetRow() * node->height + (startScrollY - startY);

	node->button->startX = node->startX - node->button->width;
	node->button->startY = node->startY;
	//子ノードがいないならボタンを無効化
	node->button->isActive = ((int)node->childNodes.size() != 0);

	for (TreeNode* childNode : node->childNodes) {
		row = UpdateNodeAndChildrenNodes(childNode, row);
	}

	return row;
}