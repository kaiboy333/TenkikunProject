#pragma once

#include <string>

class Info
{
	public:
		void SetGUID(std::string guid);
		std::string GetGUID();

	private:
		std::string guid = "0";
};

