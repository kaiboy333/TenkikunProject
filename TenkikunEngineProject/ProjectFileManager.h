#pragma once

#include <filesystem>

class ProjectFileManager
{
	public:
		static std::filesystem::path currentPath;

		static std::filesystem::path assetFilePath;

		//�A�Z�b�g�̐�΃p�X�̃t�@�C������������������
		static std::string assetParentPathName;

		ProjectFileManager();
};

