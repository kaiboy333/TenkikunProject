#include "ProjectWindow.h"
#include "TreeNode.h"
#include <filesystem>
#include "Debug.h"

ProjectWindow::ProjectWindow() : Window(0, 500, 1000, 300)
{

}

void ProjectWindow::Init()
{
	treeList = new TreeList(startX, startY, width, height, this, false, true, filesystem::current_path().filename().string());

	vector<filesystem::path> pathes;

	pathes.push_back(filesystem::current_path());

	while (pathes.size() != 0) {
		filesystem::path path = pathes[0];
		pathes.erase(pathes.begin());

		//�e�f�B���N�g���̖��O������m�[�h�ɐV�����m�[�h��ǉ�
		treeList->Add(new TreeNode(path.filename().string(), treeList, treeList->isFirstOpen), treeList->FindNode(path.parent_path().filename().string()));

		if (path.parent_path().filename().string() == ".vs") {
			Debug::Log("aaa\n");
		}

		//�f�B���N�g����������
		if (filesystem::is_directory(path)) {
			//�q�����X�g�ɒǉ�
			for (filesystem::path childPath : filesystem::directory_iterator(path)) {
				if (filesystem::is_directory(childPath)) {
					pathes.insert(pathes.begin(), childPath);
				}
				else {
					pathes.push_back(childPath);
				}
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
