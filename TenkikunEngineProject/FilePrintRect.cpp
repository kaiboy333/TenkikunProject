#include "FilePrintRect.h"
#include "ProjectFileManager.h"
#include "WindowManager.h"
#include "MyString.h"
#include "Debug.h"
#include "ImageIcon.h"

FilePrintRect::FilePrintRect(float startX, float startY, float width, float height, Window* parentWindow) : ScrollRect(startX, startY, width, height, width, height, parentWindow)
{
	//�A�C�R�����m�̋󔒕����v�Z����
	iconBetweenWidth = (width - iconWidthHeight * maxFileNumInRow) / (maxFileNumInRow + 1);

	string pathName = ProjectFileManager::currentPath.string().substr(ProjectFileManager::assetParentPathName.length());	//�e�̃p�X����A�Z�b�g�̏�̕��������������̂��擾
	pathNameRect = new TextRect(startX, startY, pathName);		//���݂̃p�X�̖��O���Z�b�g

	//�t�@�C�����h���b�v���ꂽ��
	fileDropEvents.push_back([this]() {
		for (std::filesystem::path path : ProjectFileManager::dragFilePathes) {
			MakeDuplicatedFile(path);	//�t�@�C���𕡐����Ďw��̃p�X�ɒu��
		}
	});

	//�p�X�̃t�H���_�X�V
	LoadFoler();
}

void FilePrintRect::Draw()
{
	//�g�`��
	DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(0, 0, 0), FALSE);

	//���݂̃t�@�C���p�X�`��
	pathNameRect->Draw();

	//�t�@�C���A�C�R���̕`��
	for (FileIcon* fileIcon : fileIcons) {
		fileIcon->Draw();
	}
}

void FilePrintRect::MakeDuplicatedFile(std::filesystem::path copyPath)
{
	//���݂̃p�X���擾���ăy�[�X�g�������p�X���쐬
	std::filesystem::path pastePath = ProjectFileManager::currentPath.string() + "\\" + copyPath.filename().string();

	//�t�@�C�������݂��Ȃ��Ȃ�
	if (!std::filesystem::exists(pastePath)) {
		//���̃t�@�C���^�C�v���m�F���đ��v�����Ȃ�
		if (ProjectFileManager::GetFileType(copyPath) != ProjectFileManager::FileType::None) {
			//�t�@�C�����y�[�X�g
			filesystem::copy(copyPath, pastePath);
			//�c���[���X�g�Ƀt�H���_����ǉ�
			WindowManager::projectWindow->SetFileChildrenToTreeList(pastePath);
			//�t�H���_���\���X�V
			LoadFoler();
		}
	}

}

void FilePrintRect::LoadFoler()
{
	//�O�̃A�C�R��������
	for (FileIcon* fileIcon : fileIcons) {
		//parentWindow����폜(�A�C�R��)
		parentWindow->RemoveTriggerRect(fileIcon);
		//parentWindow����폜(TextBox)
		parentWindow->RemoveTriggerRect(fileIcon->fileNameRect);
		//�X�N���[���̃��X�g������폜
		RemoveToScrollRect(fileIcon);
		//�A�C�R���ɂ���TextBox���폜
		RemoveToScrollRect(fileIcon->fileNameRect);
	}
	//���X�g�����Z�b�g
	fileIcons.clear();

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
				fileIcon = new ImageIcon(iconStartX, iconStartY, iconWidthHeight, iconWidthHeight, parentWindow, std::filesystem::relative(childPath).string(), childPath);
				break;
			case ProjectFileManager::FileType::Folder:
				//�t�H���_�A�C�R���쐬
				fileIcon = new FileIcon(iconStartX, iconStartY, iconWidthHeight, iconWidthHeight, parentWindow, "image\\folder.png", childPath);
				break;
			case ProjectFileManager::FileType::Script:
				//�X�N���v�g�A�C�R���쐬
				fileIcon = new FileIcon(iconStartX, iconStartY, iconWidthHeight, iconWidthHeight, parentWindow, "image\\script.png", childPath);
				break;
			case ProjectFileManager::FileType::None:
				//�������Ȃ�
				break;
			}

			//�t�@�C���A�C�R�����쐬����Ă���Ȃ�
			if (fileIcon) {
				//���X�g�ɒǉ�
				fileIcons.push_back(fileIcon);
				//Scroll�̃��X�g�ɃA�C�R����ǉ�(&�X�V)
				AddToScrollRect(fileIcon);
				//�A�C�R���ɂ���TextBox���o�^
				AddToScrollRect(fileIcon->fileNameRect);
				//���̔ԍ���
				iconNum++;
			}

		}
	}
}
