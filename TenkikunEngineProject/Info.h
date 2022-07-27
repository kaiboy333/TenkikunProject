#pragma once

#include <string>
#include "SceneInfo.h"
#include <filesystem>

class Info : public SceneInfo
{
	public:
		std::filesystem::path path;

		std::string name;

		Info(std::filesystem::path path, bool canWrite = true);	//canWrite:‘‚«‚İ‰Â”\‚©

		std::string guid = "0";
};

