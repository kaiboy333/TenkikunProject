#include "FilePrintRect.h"

FilePrintRect::FilePrintRect(float startX, float startY, float width, float height, Window* parentWindow) : TriggerRect(startX, startY, width, height, parentWindow)
{
	DragFileInfoClear();	//�h���b�v�t�@�C�����̏�����
	SetAlwaysRunFlag(true);		//�o�b�N�O���E���h�ł�������p��
	SetDragFileValidFlag(true);		//�h���b�O�A���h�h���b�v������

	//�t�@�C�����h���b�v���ꂽ��
	fileDropEvents.push_back([this]() {
		TCHAR currentPath[100] = {};
		//�t�@�C�����ǂݍ��߂���
		if (GetDragFilePath(currentPath) != -1) {
			//this->currentPath = currentPath;	//�p�X���L��
		}
		else {
			//this->currentPath = "";
		}
	});

}

void FilePrintRect::Draw()
{
	//DrawStringF(startX, startY + height / 2, currentPath.filename().string().c_str(), GetColor(0, 0, 0));
}
