#include "ProjectWindow.h"
#include "TreeNode.h"
#include <filesystem>
#include "Debug.h"
#include "MyString.h"
#include "ProjectFileManager.h"

ProjectWindow::ProjectWindow() : Window(0, 500, 1000, 300)
{
}

void ProjectWindow::Init()
{
	//ツリーリスト作成
	treeList = new TreeList(startX, startY, WindowManager::hierarchyWindow->width, height, false, true, ProjectFileManager::assetFilePath.filename().string());

	//ツリーリストにパスを追加
	SetFileChildrenToTreeList(ProjectFileManager::assetFilePath);

	filePrintRect = new FilePrintRect(WindowManager::hierarchyWindow->width, startY, width - WindowManager::hierarchyWindow->width, height);
	//ファイルアイコン更新
	filePrintRect->LoadFoler();
}

void ProjectWindow::Update()
{
	Window::Update();
}

void ProjectWindow::Draw()
{
	Window::Draw();

	if (treeList) {
		treeList->Draw();
	}

	filePrintRect->Draw();
}

void ProjectWindow::SetFileChildrenToTreeList(std::filesystem::path path)
{
	vector<filesystem::path> pathes;

	pathes.push_back(path);

	//ツリーリストにアセットのパスを追加
	while (pathes.size() != 0) {
		filesystem::path path = pathes[0];
		pathes.erase(pathes.begin());

		//パスがディレクトリだったら
		if (filesystem::is_directory(path)) {
			//ノード作成
			TreeNode* node = new TreeNode(path.filename().string(), treeList, treeList->isFirstOpen);

			//イベントを追加(ダブルクリックをしたら)
			node->mouseDoubleClickEvents.push_back(std::make_pair(node->GetEventNo(), [this, node]() {
				//クリックしたノードから絶対パスを求める
				std::filesystem::path path = std::filesystem::path(ProjectFileManager::assetParentPathName + node->GetPath());
				//現在のパスにさっきのパスを入れる
				ProjectFileManager::currentPath = path;
				//パス内のフォルダ更新
				filePrintRect->LoadFoler();
			}));

			if (path != ProjectFileManager::assetFilePath) {
				//親のパスからアセットの上の部分を除いたものを取得
				string parentPathName = path.parent_path().string().substr(ProjectFileManager::assetParentPathName.length());
				//親ディレクトリの名前があるノードに新しくノードを追加
				//treeList->Add(node, treeList->FindNode(MyString::Split(parentPathName, "\\")));
				treeList->Add(node, treeList->FindNode(parentPathName));
			}

			//子をリストに追加
			for (filesystem::path childPath : filesystem::directory_iterator(path)) {
				pathes.push_back(childPath);
			}
		}
	}
}

void ProjectWindow::PreparationLibrate()
{
	//TreeListの解放準備
	treeList->PreparationLibrate();
	//解放
	delete(treeList);
	treeList = nullptr;

	//FilePrintRectの解放準備
	filePrintRect->PreparationLibrate();
	//解放
	delete(filePrintRect);
	filePrintRect = nullptr;

	//自身の解放準備
	Window::PreparationLibrate();
}
