#include "FolderIcon.h"
#include "WindowManager.h"
#include "ProjectFileManager.h"

FolderIcon::FolderIcon(float startX, float startY, float iconWidth, float iconHeight, float blankWidth, float blankHeight, Window* parentWindow, std::string imageFileName, std::filesystem::path path) : FileIcon(startX, startY, iconWidth, iconHeight, blankWidth, blankHeight, parentWindow, imageFileName, path)
{
	//�C�x���g��ǉ�(�_�u���N���b�N��������)
	this->mouseDoubleClickEvents.push_back([this]() {
		//���݂̃p�X�ɂ������̃p�X������
		ProjectFileManager::currentPath = this->path;
		//�p�X���̃t�H���_�X�V
		WindowManager::projectWindow->filePrintRect->LoadFoler();
	});
}

