#pragma once

#include <filesystem>

class ProjectFileManager
{
	public:
		//�t�@�C���̎��
		enum class FileType {
			Image,
			Folder,
			Script,
			None,
		};

		static std::filesystem::path currentPath;	//���݂̃p�X

		static std::filesystem::path assetFilePath;	//�A�Z�b�g�t�H���_������p�X

		//�A�Z�b�g�̐�΃p�X�̃t�@�C������������������
		static std::string assetParentPathName;

		//�h���b�O���ꂽ�t�@�C���̃p�X����
		static std::vector<std::filesystem::path> dragFilePathes;

		ProjectFileManager();

		static void Update();

		static FileType GetFileType(std::filesystem::path path);	//�w��̃t�@�C���͂��̃^�C�v�ł��邩
};

