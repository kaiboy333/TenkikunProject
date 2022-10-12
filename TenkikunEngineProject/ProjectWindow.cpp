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
	//�c���[���X�g�쐬
	treeList = new TreeList(startX, startY, WindowManager::hierarchyWindow->width, height, false, true, ProjectFileManager::assetFilePath.filename().string());

	//�c���[���X�g�Ƀp�X��ǉ�
	SetFileChildrenToTreeList(ProjectFileManager::assetFilePath);

	filePrintRect = new FilePrintRect(WindowManager::hierarchyWindow->width, startY, width - WindowManager::hierarchyWindow->width, height);
	//�t�@�C���A�C�R���X�V
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

	//�c���[���X�g�ɃA�Z�b�g�̃p�X��ǉ�
	while (pathes.size() != 0) {
		filesystem::path path = pathes[0];
		pathes.erase(pathes.begin());

		//�p�X���f�B���N�g����������
		if (filesystem::is_directory(path)) {
			//�m�[�h�쐬
			TreeNode* node = new TreeNode(path.filename().string(), treeList, treeList->isFirstOpen);

			//�C�x���g��ǉ�(�_�u���N���b�N��������)
			node->mouseDoubleClickEvents.push_back(std::make_pair(node->GetEventNo(), [this, node]() {
				//�N���b�N�����m�[�h�����΃p�X�����߂�
				std::filesystem::path path = std::filesystem::path(ProjectFileManager::assetParentPathName + node->GetPath());
				//���݂̃p�X�ɂ������̃p�X������
				ProjectFileManager::currentPath = path;
				//�p�X���̃t�H���_�X�V
				filePrintRect->LoadFoler();
			}));

			if (path != ProjectFileManager::assetFilePath) {
				//�e�̃p�X����A�Z�b�g�̏�̕��������������̂��擾
				string parentPathName = path.parent_path().string().substr(ProjectFileManager::assetParentPathName.length());
				//�e�f�B���N�g���̖��O������m�[�h�ɐV�����m�[�h��ǉ�
				//treeList->Add(node, treeList->FindNode(MyString::Split(parentPathName, "\\")));
				treeList->Add(node, treeList->FindNode(parentPathName));
			}

			//�q�����X�g�ɒǉ�
			for (filesystem::path childPath : filesystem::directory_iterator(path)) {
				pathes.push_back(childPath);
			}
		}
	}
}

void ProjectWindow::PreparationLibrate()
{
	//TreeList�̉������
	treeList->PreparationLibrate();
	//���
	delete(treeList);
	treeList = nullptr;

	//FilePrintRect�̉������
	filePrintRect->PreparationLibrate();
	//���
	delete(filePrintRect);
	filePrintRect = nullptr;

	//���g�̉������
	Window::PreparationLibrate();
}
