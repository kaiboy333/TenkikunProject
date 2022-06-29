#pragma once
#include "TriggerRect.h"
#include <filesystem>
#include "FileIcon.h"
#include <string>

class FilePrintRect :  public TriggerRect
{
	public:
		float iconWidthHeight = 50;	//�\������A�C�R���̕��A����
		int maxFileNumInRow = 10;	//�s�ɕ\���ł���ő�̃t�@�C���̐�
		float iconBetweenWidth;	//�A�C�R�����m�̋󔒂̕�

		std::vector<FileIcon*> fileIcons;	//�t�@�C���A�C�R������

		FilePrintRect(float startX, float startY, float width, float height, Window* parentWindow);

		void Draw();

		void LoadFoler();	//���݂̂̃p�X��ǂݍ��ݒ��g���X�V

	private:
		void MakeDuplicatedFile(std::filesystem::path copyPath);	//�h���b�v���ꂽ�t�@�C�����w��p�X�쐬
};

