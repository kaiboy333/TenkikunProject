#include "FilePrintRect.h"
#include "ProjectFileManager.h"
#include "WindowManager.h"
#include "MyString.h"
#include "Debug.h"

FilePrintRect::FilePrintRect(float startX, float startY, float width, float height, Window* parentWindow) : TriggerRect(startX, startY, width, height, parentWindow)
{
	iconBetweenWidth = (parentWindow->width - iconWidthHeight * maxFileNumInRow) / (maxFileNumInRow + 1);

	DragFileInfoClear();	//�h���b�v�t�@�C�����̏�����
	SetAlwaysRunFlag(true);		//�o�b�N�O���E���h�ł�������p��
	SetDragFileValidFlag(true);		//�h���b�O�A���h�h���b�v������

	//�t�@�C�����h���b�v���ꂽ��
	fileDropEvents.push_back([this]() {
		for (std::filesystem::path path : ProjectFileManager::dragFilePathes) {
			DropFileCheck(path);	//�t�@�C���̃`�F�b�N
		}
	});
}

void FilePrintRect::Draw()
{
	//�`��͈͐���
	SetDrawArea(startX, startY, startX + width - 1, startY + height - 1);

	//���݂̃t�@�C���p�X�`��
	DrawStringF(startX, startY, ProjectFileManager::currentPath.string().c_str(), GetColor(0, 0, 0));

	//�t�@�C���A�C�R���̕`��
	for (FileIcon* fileIcon : fileIcons) {
		fileIcon->IconDraw();
	}
}

void FilePrintRect::DropFileCheck(std::filesystem::path path)
{
	//�p�X�̊g���q���擾
	std::string extensionName = path.extension().string();

	//���݂̃p�X���擾���ăy�[�X�g�������p�X���쐬
	std::filesystem::path pastePath = ProjectFileManager::currentPath.string() + "\\" + path.filename().string();

	//�t�@�C�������݂��Ȃ��Ȃ�
	if (!std::filesystem::exists(pastePath)) {
		//�摜�̊g���q�Ȃ�
		if (extensionName == ".png" || extensionName == ".jpg") {
			int iconNum = fileIcons.size();
			//���s����ڂɍ�邩�v�Z����
			int row = iconNum / maxFileNumInRow;
			int col = iconNum % maxFileNumInRow;
			//�t�@�C�����R�s�[���Č��݂̃p�X�Ƀy�[�X�g
			std::filesystem::copy_file(path, pastePath);
			//�摜�̃A�C�R���쐬
			FileIcon* fileIcon = new FileIcon(startX + (col + 1) * iconBetweenWidth + col * iconWidthHeight, startY + (row + 1) * iconBetweenWidth + row * iconWidthHeight, iconWidthHeight, iconWidthHeight, parentWindow, std::filesystem::relative(pastePath).string(), pastePath);
			fileIcons.push_back(fileIcon);
		}
	}

}
