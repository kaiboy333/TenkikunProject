#pragma once

#include <vector>
#include <string>
#include <sstream>

class MyString
{
	public:
		static std::vector<std::string> Split(std::string str, char splitChar);	//strをsplitCharごとに文字分割して返す
};

