#pragma once
#include "ScrollRect.h"
#include <filesystem>
#include "FileIcon.h"
#include <string>

class TextRect;
class FilePrintRect :  public ScrollRect
{
	public:
		float iconWidthHeight = 50;	//�\������A�C�R���̕��A����
		const int maxFileNumInRow = 7;	//�s�ɕ\���ł���ő�̃t�@�C���̐�
		float iconBetweenWidth;	//�A�C�R�����m�̋󔒂̕�

		std::vector<FileIcon*> fileIcons;	//�t�@�C���A�C�R������

		TextRect* pathNameRect = nullptr;	//���݂̃p�X�̖��O��TextRect

		FilePrintRect(float startX, float startY, float width, float height, Window* parentWindow);

		void Draw();

		void LoadFoler();	//���݂̃p�X��ǂݍ��ݒ��g���X�V

	private:
		void MakeDuplicatedFile(std::filesystem::path copyPath);	//�h���b�v���ꂽ�t�@�C�����w��p�X�쐬
};

