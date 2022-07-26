#pragma once

#include <string>
#include "SceneInfo.h"
#include <filesystem>

class Info : public SceneInfo
{
	public:
		std::filesystem::path path;

		std::string name;

		Info();

		//void SetGUID(std::string guid);
		std::string GetGUID();

	private:
		std::string guid = "0";
};

