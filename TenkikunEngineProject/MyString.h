#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <filesystem>

class MyString
{
	public:
		static std::vector<std::string> Split(std::string str, char splitChar);	//strをsplitCharごとに文字分割して返す

		static std::vector<std::string> GetLines(std::filesystem::path path);	//ファイルの行を読み込み、リストを取得
};

