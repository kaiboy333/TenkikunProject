#include "ProjectFileManager.h"

ProjectFileManager::ProjectFileManager()
{
	//�A�Z�b�g�̃p�X���쐬
	assetFilePath = std::filesystem::current_path().string() + "\\Asset";
	//�A�Z�b�g�̐e�̐�΃p�X�Ƀo�b�N�X���b�V���ǉ�
	assetParentPathName = assetFilePath.parent_path().string() + "\\";
	//�A�Z�b�g�t�H���_�����݂��Ȃ��Ȃ�
	if (!std::filesystem::exists(assetFilePath)) {
		//�t�H���_���쐬
		std::filesystem::create_directory(assetFilePath);
	}
	//�����̌��݃p�X�̓A�Z�b�g�t�H���_�ɂ���
	currentPath = assetFilePath;
}

std::filesystem::path ProjectFileManager::currentPath;

std::filesystem::path ProjectFileManager::assetFilePath;

std::string ProjectFileManager::assetParentPathName = "";
