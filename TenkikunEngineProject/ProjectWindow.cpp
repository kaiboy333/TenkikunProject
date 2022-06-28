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

		//�p�X���f�B���N�g����������
		if (filesystem::is_directory(path)) {
			//�p�X���A�Z�b�g�t�H���_����Ȃ��Ȃ�
			if (path != ProjectFileManager::assetFilePath) {
				//�e�̃p�X����A�Z�b�g�̏�̕��������������̂��擾
				string parentPathName = path.parent_path().string().substr(ProjectFileManager::assetParentPathName.length());
				//�e�f�B���N�g���̖��O������m�[�h�ɐV�����m�[�h��ǉ�
				treeList->Add(new TreeNode(path.filename().string(), treeList, treeList->isFirstOpen), treeList->FindNode(MyString::Split(parentPathName, '\\')));
			}

			//�q�����X�g�ɒǉ�
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
