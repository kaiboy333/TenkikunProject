#pragma once

#include <string>
#include "SceneInfo.h"
#include <filesystem>

class Info : public SceneInfo
{
	public:
		std::filesystem::path path;

		std::string name;

		Info(std::filesystem::path path, bool canWrite = true);	//canWrite:書き込み可能か

		std::string guid = "0";

		virtual void PreparationLibrate() = 0;
};

