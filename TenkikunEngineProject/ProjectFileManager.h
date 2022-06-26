#pragma once

#include <filesystem>

class ProjectFileManager
{
	public:
		static std::filesystem::path currentPath;

		static std::filesystem::path assetFilePath;

		//アセットの絶対パスのファイル名だけ除いたもの
		static std::string assetParentPathName;

		ProjectFileManager();
};

