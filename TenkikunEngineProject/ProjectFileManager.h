#pragma once

#include <filesystem>

class ProjectFileManager
{
	public:
		static std::filesystem::path currentPath;

		static std::filesystem::path assetFilePath;

		//�A�Z�b�g�̐�΃p�X�̃t�@�C������������������
		static std::string assetParentPathName;

		//�h���b�O���ꂽ�t�@�C���̃p�X����
		static std::vector<std::filesystem::path> dragFilePathes;

		ProjectFileManager();

		static void Update();
};

