#include "ProjectWindow.h"
#include "TreeNode.h"
#include <filesystem>

ProjectWindow::ProjectWindow() : Window(0, 500, 1000, 300)
{

}

void ProjectWindow::Init()
{
	treeList = new TreeList(this, true, filesystem::current_path().filename().string());

	vector<filesystem::path> pathes;

	pathes.push_back(filesystem::current_path());

	while (pathes.size() != 0) {
		filesystem::path path = pathes[0];
		pathes.erase(pathes.begin());

		//親ディレクトリの名前があるノードに新しくノードを追加
		treeList->Add(new TreeNode(path.filename().string(), treeList), treeList->FindNode(path.parent_path().filename().string()));

		//ディレクトリだったら
		if (filesystem::is_directory(path)) {
			//子ディレクトリをリストに追加
			for (auto childPath : filesystem::directory_iterator(path)) {
				pathes.push_back(childPath);
			}
		}
	}

	projectFileManager = new ProjectFileManager(this->startX, this->startY, this->width, this->height, this);
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

	projectFileManager->Draw();
}
