#include "ProjectFileManager.h"
#include "DxLib.h"

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
	currentPath = assetFilePath;	//�����̓A�Z�b�g�p�X
}

void ProjectFileManager::Update()
{
	//�h���b�O�t�@�C�����X�g�̃��Z�b�g
	dragFilePathes.clear();
	//�h���b�O����Ă���t�@�C��������Ȃ�
	if (GetDragFileNum != 0) {
		for (int i = 0; i < GetDragFileNum(); i++) {
			TCHAR currentPath[100] = {};
			//�ǂݍ��߂���
			if (GetDragFilePath(currentPath) != -1) {
				//�h���b�O���ꂽ�t�@�C���̃p�X���쐬
				std::filesystem::path path = std::filesystem::path(std::string(currentPath));
				//���X�g�ɒǉ�
				dragFilePathes.push_back(path);
			}
		}
	}
}

ProjectFileManager::FileType ProjectFileManager::GetFileType(std::filesystem::path path) {
	//�p�X�̊g���q���擾
	std::string extensionName = path.extension().string();

	//������
	FileType targetFileType = FileType::None;

	//�p�X���f�B���N�g����������
	if (std::filesystem::is_directory(path)) {
		targetFileType = FileType::Folder;
	}
	else {
		//�摜��������
		if (extensionName == ".png" || extensionName == ".jpg") {
			targetFileType = FileType::Image;
		}
		//�X�N���v�g��������
		else if (extensionName == ".cpp" || extensionName == ".h" || extensionName == ".hpp") {
			targetFileType = FileType::Script;
		}
	}

	//�^�C�v��Ԃ�
	return targetFileType;
}

std::filesystem::path ProjectFileManager::assetFilePath;

std::filesystem::path ProjectFileManager::currentPath;

std::string ProjectFileManager::assetParentPathName = "";

std::vector<std::filesystem::path> ProjectFileManager::dragFilePathes;
