#include "FilePrintRect.h"
#include "ProjectFileManager.h"
#include "WindowManager.h"
#include "MyString.h"
#include "Debug.h"
#include "ImageIcon.h"
#include "FolderIcon.h"
#include "ScriptIcon.h"

FilePrintRect::FilePrintRect(float startX, float startY, float width, float height) : ScrollRect(startX, startY, width, height, width, height)
{
	//�A�C�R�����m�̋󔒕����v�Z����
	iconBetweenWidth = (width - iconWidthHeight * maxFileNumInRow) / (maxFileNumInRow + 1);

	string pathName = ProjectFileManager::currentPath.string().substr(ProjectFileManager::assetParentPathName.length());	//�e�̃p�X����A�Z�b�g�̏�̕��������������̂��擾
	pathNameRect = new TextRect(startX, startY, pathName);		//���݂̃p�X�̖��O���Z�b�g

	//�t�@�C�����h���b�v���ꂽ��
	fileDropEvents.push_back(std::make_pair(GetEventNo(), [this]() {
		for (std::filesystem::path path : ProjectFileManager::dragFilePathes) {
			MakeDuplicatedFile(path);	//�t�@�C���𕡐����Ďw��̃p�X�ɒu��
		}
	}));

	//�E�N���b�N����������
	mouseRightClickEvents.push_back(std::make_pair(GetEventNo(), [this]() {
		Vector3 mousePos = Input::GetMousePosition();

		MenuList* menuList0 = new MenuList(mousePos.x, mousePos.y, { "Create", "Delete", "B", "C" });
		//WindowManager�ɃZ�b�g
		WindowManager::SetMenuList(menuList0);

		MenuNode* menuNode0_0 = menuList0->FindNode("Create");
		MenuList* menuList1 = new MenuList(menuNode0_0->startX + menuNode0_0->width, menuNode0_0->startY, { "Folder", "C++ Script" });
		MenuNode* menuNode1_0 = menuList1->FindNode("Folder");
		menuNode1_0->mouseClickDownEvents.insert(menuNode1_0->mouseClickDownEvents.begin(), std::make_pair(menuNode1_0->GetEventNo(), []() {
			//�t�H���_���쐬
			std::filesystem::path folderPath = ProjectFileManager::currentPath.string() + "\\Folder";
			//�t�@�C�������݂��Ȃ��Ȃ�
			if (!std::filesystem::exists(folderPath)) {
				////���̃t�@�C���^�C�v���m�F���đ��v�����Ȃ�
				//if (ProjectFileManager::IsFileType(folderPath)) {
					//�t�H���_���쐬
					std::filesystem::create_directory(folderPath);
					//�t�@�C�����`�F�b�N
					ProjectFileManager::CheckAddFile(folderPath);
					//�c���[���X�g�Ƀt�H���_����ǉ�
					WindowManager::projectWindow->SetFileChildrenToTreeList(folderPath);
					//�t�H���_���\���X�V
					WindowManager::projectWindow->filePrintRect->LoadFoler();
				//}
			}
		}));
		MenuNode* menuNode1_1 = menuList1->FindNode("C++ Script");
		menuNode1_1->mouseClickDownEvents.insert(menuNode1_1->mouseClickDownEvents.begin(), std::make_pair(menuNode1_1->GetEventNo(), []() {
			//�X�N���v�g���쐬
			std::vector<std::filesystem::path> scriptPathes;
			//.h
			scriptPathes.push_back(std::filesystem::path(ProjectFileManager::currentPath.string() + "\\Script.h"));
			//.cpp
			scriptPathes.push_back(std::filesystem::path(ProjectFileManager::currentPath.string() + "\\Script.cpp"));
			for (auto& scriptPath : scriptPathes) {
				//�t�@�C�������݂��Ȃ��Ȃ�
				if (!std::filesystem::exists(scriptPath)) {
					//���̃t�@�C���^�C�v���m�F���đ��v�����Ȃ�
					if (ProjectFileManager::IsFileType(scriptPath)) {
						//�t�@�C�����쐬
						std::ofstream ofs(scriptPath);
						//�t�@�C�����`�F�b�N
						ProjectFileManager::CheckAddFile(scriptPath);
						//�c���[���X�g�Ƀt�H���_����ǉ�
						WindowManager::projectWindow->SetFileChildrenToTreeList(scriptPath);
						//�t�H���_���\���X�V
						WindowManager::projectWindow->filePrintRect->LoadFoler();
					}
				}
			}
		}));
		//���j���[�m�[�h�Ƀ��j���[���X�g���Z�b�g
		menuNode0_0->SetChildMenuList(menuList1);
	}));
}

void FilePrintRect::Draw()
{
	//�g�`��
	DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(0, 0, 0), FALSE);

	//�t�@�C���A�C�R���̕`��
	for (FileIcon* fileIcon : fileIcons) {
		fileIcon->Draw();
	}

	DrawBoxAA(pathNameRect->startX, pathNameRect->startY, pathNameRect->startX + width, pathNameRect->startY + pathNameRect->height, GetColor(255, 255, 255), TRUE);
	//���݂̃t�@�C���p�X�`��
	pathNameRect->Draw();
	DrawBoxAA(pathNameRect->startX, pathNameRect->startY, pathNameRect->startX + width, pathNameRect->startY + pathNameRect->height, GetColor(0, 0, 0), FALSE);
}

void FilePrintRect::MakeDuplicatedFile(std::filesystem::path copyPath)
{
	//���݂̃p�X���擾���ăy�[�X�g�������p�X���쐬
	std::filesystem::path pastePath = ProjectFileManager::currentPath.string() + "\\" + copyPath.filename().string();

	//�t�@�C�������݂��Ȃ��Ȃ�
	if (!std::filesystem::exists(pastePath)) {
		//���̃t�@�C���^�C�v���m�F���đ��v�����Ȃ�
		if (ProjectFileManager::IsFileType(copyPath)) {
			//�t�@�C�����y�[�X�g
			filesystem::copy(copyPath, pastePath);
			//�t�@�C�����`�F�b�N
			ProjectFileManager::CheckAddFile(pastePath);
			//�c���[���X�g�Ƀt�H���_����ǉ�
			WindowManager::projectWindow->SetFileChildrenToTreeList(pastePath);
			//�t�H���_���\���X�V
			LoadFoler();
		}
	}

}

void FilePrintRect::PreparationLibrate()
{
	//�O�̃A�C�R��������
	for (FileIcon* fileIcon : fileIcons) {
		//�X�N���[���̃��X�g������폜
		RemoveToScrollRect(fileIcon);
		//�A�C�R���ɂ���TextBox���폜
		RemoveToScrollRect(fileIcon->fileNameRect);
		
		//�A�C�R���̉������
		fileIcon->PreparationLibrate();
		//���
		delete(fileIcon);
		fileIcon = nullptr;
	}
	//���X�g�����Z�b�g
	fileIcons.clear();

	//TextRect�������
	pathNameRect->PreparationLibrate();
	//���
	delete(pathNameRect);
	pathNameRect = nullptr;

}

void FilePrintRect::LoadFoler()
{
	//�������(���Z�b�g)
	PreparationLibrate();

	//�X�N���[���̃��Z�b�g
	InitScrollPos();

	//���݂̃p�X�̖��O���Z�b�g
	string pathName = ProjectFileManager::currentPath.string().substr(ProjectFileManager::assetParentPathName.length());	//�e�̃p�X����A�Z�b�g�̏�̕��������������̂��擾
	pathNameRect = new TextRect(startX, startY, pathName);		//���݂̃p�X�̖��O���Z�b�g

	//�p�X���f�B���N�g����������
	if (filesystem::is_directory(ProjectFileManager::currentPath)) {
		int iconNum = 0;
		//���g���Q��
		for (filesystem::path childPath : filesystem::directory_iterator(ProjectFileManager::currentPath)) {
			//���s����ڂɍ�邩�v�Z����
			int row = iconNum / maxFileNumInRow;
			int col = iconNum % maxFileNumInRow;

			//�t�@�C���^�C�v���`�F�b�N���Ă��ꂼ��̏���������(��ɃA�C�R�����쐬)
			FileIcon* fileIcon = nullptr;
			float iconStartX = startX + (col + 1) * iconBetweenWidth + col * iconWidthHeight;
			float iconStartY = startY + (row + 1) * iconBetweenWidth + row * iconWidthHeight;
			switch (ProjectFileManager::GetFileType(childPath)) {
				case ProjectFileManager::FileType::Image:
					//�C���[�W�A�C�R���쐬
					fileIcon = new ImageIcon(iconStartX, iconStartY, iconWidthHeight, iconWidthHeight, 10, 5, std::filesystem::relative(childPath).string(), childPath);
					break;
				case ProjectFileManager::FileType::Folder:
					//�t�H���_�A�C�R���쐬
					fileIcon = new FolderIcon(iconStartX, iconStartY, iconWidthHeight, iconWidthHeight, 10, 5, ProjectFileManager::imageFilePath.string() + "\\folder.png", childPath);
					break;
				case ProjectFileManager::FileType::Script_cpp:
					//�X�N���v�g(cpp)�A�C�R���쐬
					fileIcon = new ScriptIcon(iconStartX, iconStartY, iconWidthHeight, iconWidthHeight, 10, 5, ProjectFileManager::imageFilePath.string() + "\\script_cpp.png", childPath);
					break;
				case ProjectFileManager::FileType::Script_hpp:
					//�X�N���v�g(hpp)�A�C�R���쐬
					fileIcon = new ScriptIcon(iconStartX, iconStartY, iconWidthHeight, iconWidthHeight, 10, 5, ProjectFileManager::imageFilePath.string() + "\\script_hpp.png", childPath);
					break;
				case ProjectFileManager::FileType::Script_h:
					//�X�N���v�g(h)�A�C�R���쐬
					fileIcon = new ScriptIcon(iconStartX, iconStartY, iconWidthHeight, iconWidthHeight, 10, 5, ProjectFileManager::imageFilePath.string() + "\\script_h.png", childPath);
					break;
				case ProjectFileManager::FileType::Scene:
					//�V�[���A�C�R���쐬
					fileIcon = new FileIcon(iconStartX, iconStartY, iconWidthHeight, iconWidthHeight, 10, 5, ProjectFileManager::imageFilePath.string() + "\\Tenkikun.png", childPath);
					break;
				case ProjectFileManager::FileType::None:
					//�������Ȃ�
					break;
			}

			//�t�@�C���A�C�R�����쐬����Ă���Ȃ�
			if (fileIcon) {
				//Scroll�̃��X�g�ɃA�C�R����ǉ�(&�X�V)
				AddToScrollRect(fileIcon);
				//�A�C�R���ɂ���TextBox���o�^
				AddToScrollRect(fileIcon->fileNameRect);
				//���X�g�ɒǉ�
				fileIcons.push_back(fileIcon);
				//���̔ԍ���
				iconNum++;
			}

		}
	}

	int row = (int)fileIcons.size() / maxFileNumInRow;
	if ((int)fileIcons.size() % maxFileNumInRow != 0) {
		row++;
	}
	scrollHeight = (row + 1) * iconBetweenWidth + row * (iconWidthHeight + FileIcon::overWidth);
	ScrollUpdate();
}
