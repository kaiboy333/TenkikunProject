#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <filesystem>

class MyString
{
	public:
		static std::vector<std::string> Split(std::string str, char splitChar);	//str��splitChar���Ƃɕ����������ĕԂ�

		static std::vector<std::string> GetLines(std::filesystem::path path);	//�t�@�C���̍s��ǂݍ��݁A���X�g���擾
};

