#pragma once

#include <string>
#include "SceneInfo.h"

class Info : public SceneInfo
{
	public:
		void SetGUID(std::string guid);
		std::string GetGUID();

	private:
		std::string guid = "0";
};

