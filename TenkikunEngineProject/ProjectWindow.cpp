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
	treeList = new TreeList(startX, startY, WindowManager::hierarchyWindow->width, height, this, false, true, ProjectFileManager::assetFilePath.filename().string());

	vector<filesystem::path> pathes;

	pathes.push_back(ProjectFileManager::assetFilePath);

	//�c���[���X�g�ɃA�Z�b�g�̃p�X��ǉ�
	SetFileChildrenToTreeList(ProjectFileManager::assetFilePath);

	filePrintRect = new FilePrintRect(WindowManager::hierarchyWindow->width, startY, width - WindowManager::hierarchyWindow->width, height, this);
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

void ProjectWindow::SetFileChildrenToTreeList(std::filesystem::path addPath)
{
	vector<filesystem::path> pathes;

	pathes.push_back(addPath);

	//�c���[���X�g�ɃA�Z�b�g�̃p�X��ǉ�
	while (pathes.size() != 0) {
		filesystem::path path = pathes[0];
		pathes.erase(pathes.begin());

		//�_�t�@�C�����Ȃ���΍쐬�A�ǂݍ���
		ProjectFileManager::CreateAndLoadKumoFile(path);

		//�p�X���f�B���N�g����������
		if (filesystem::is_directory(path)) {
			//�m�[�h�쐬
			TreeNode* node = new TreeNode(path.filename().string(), treeList, treeList->isFirstOpen);

			//�C�x���g��ǉ�
			node->mouseClickDownEvents.push_back([this, node]() {
				//�N���b�N�����m�[�h�����΃p�X�����߂�
				std::filesystem::path path = std::filesystem::path(ProjectFileManager::assetParentPathName + node->GetPath());
				//���݂̃p�X�ɂ������̃p�X������
				ProjectFileManager::currentPath = path;
				//�p�X���̃t�H���_�X�V
				filePrintRect->LoadFoler();
			});

			//�p�X���A�Z�b�g�t�H���_����Ȃ��Ȃ�
			if (path != ProjectFileManager::assetFilePath) {
				//�e�̃p�X����A�Z�b�g�̏�̕��������������̂��擾
				string parentPathName = path.parent_path().string().substr(ProjectFileManager::assetParentPathName.length());
				//�e�f�B���N�g���̖��O������m�[�h�ɐV�����m�[�h��ǉ�
				treeList->Add(node, treeList->FindNode(MyString::Split(parentPathName, '\\')));
			}

			//�q�����X�g�ɒǉ�
			for (filesystem::path childPath : filesystem::directory_iterator(path)) {
				pathes.push_back(childPath);
			}
		}
		else {
			//�t�@�C�����V�[���t�@�C���Ȃ�
			if (ProjectFileManager::GetFileType(path) == ProjectFileManager::FileType::Scene) {
				std::string sceneName = path.filename().string().substr(0, path.filename().string().length() - path.extension().string().length());
				//�V�[���̃}�b�v�ɖ���������
				if (!SceneManager::scenePathes.contains(sceneName)) {
					//�V�[���}�l�[�W���[�̃��X�g�ɒǉ�
					SceneManager::scenePathes.insert(std::make_pair(sceneName, path));
				}
			}
		}
	}
}
