#pragma once

#include <filesystem>
#include <unordered_map>
#include "Info.h"

class ProjectFileManager
{
	public:
		//�t�@�C���̎��
		enum class FileType {
			Image,
			Folder,
			Script_cpp,
			Script_hpp,
			Script_h,
			Kumo,
			None,
		};

		static std::filesystem::path currentPath;	//���݂̃p�X

		static std::filesystem::path assetFilePath;	//�A�Z�b�g�t�H���_������p�X

		//�A�Z�b�g�̐�΃p�X�̃t�@�C������������������
		static std::string assetParentPathName;

		//�h���b�O���ꂽ�t�@�C���̃p�X����
		static std::vector<std::filesystem::path> dragFilePathes;

		//Info������������
		static std::unordered_map<std::string, Info*> idInfos;

		ProjectFileManager();

		static void Update();

		static FileType GetFileType(std::filesystem::path path);	//�w��̃t�@�C���͂��̃^�C�v�ł��邩

		static void CreateAndLoadKumoFile(std::filesystem::path kumoPath);	//�t�@�C����p�̂���(���^)�t�@�C�����`�F�b�N

	private:
		static void WriteToKumoFile(std::filesystem::path kumoPath);	//�_�t�@�C���ɋL�q����
		static void WriteToInfo(std::filesystem::path kumoPath);	//�_�t�@�C������Info���쐬

		static std::string CreateGUID();	//GUID�𐶐�����(string��)
};

