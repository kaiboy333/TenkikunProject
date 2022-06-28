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
	treeList = new TreeList(startX, startY, WindowManager::hierarchyWindow->width, height, this, false, true, ProjectFileManager::assetFilePath.filename().string());

	vector<filesystem::path> pathes;

	pathes.push_back(ProjectFileManager::assetFilePath);

	while (pathes.size() != 0) {
		filesystem::path path = pathes[0];
		pathes.erase(pathes.begin());

		//パスがディレクトリだったら
		if (filesystem::is_directory(path)) {
			//パスがアセットフォルダじゃないなら
			if (path != ProjectFileManager::assetFilePath) {
				//親のパスからアセットの上の部分を除いたものを取得
				string parentPathName = path.parent_path().string().substr(ProjectFileManager::assetParentPathName.length());
				//親ディレクトリの名前があるノードに新しくノードを追加
				treeList->Add(new TreeNode(path.filename().string(), treeList, treeList->isFirstOpen), treeList->FindNode(MyString::Split(parentPathName, '\\')));
			}

			//子をリストに追加
			for (filesystem::path childPath : filesystem::directory_iterator(path)) {
				pathes.push_back(childPath);
			}
		}

	}

	filePrintRect = new FilePrintRect(WindowManager::hierarchyWindow->width, this->startY, this->width - WindowManager::hierarchyWindow->width, this->height, this);
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
