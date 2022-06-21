#include "ImageManager.h"
#include "DxLib.h"
#include "Image.h"
#include <sstream>

ImageManager::ImageManager() {

}

int* ImageManager::LoadAndGetImage(std::string path)
{
	//�����A���ɉ摜���ǂݍ��܂�Ă����Ȃ�
	if (ghs.count(path.c_str())) {
		return ghs[path.c_str()];	//�����Ԃ�
	}

	//�摜��V�����ǂݍ���
	int* gh = new int;		//GraphicHandle
	*gh = LoadGraph(path.c_str());
	//�摜���ǂݍ��߂Ȃ�������
	if (*gh == -1) {
		std::stringstream ss;
		ss << "�摜�t�@�C�����ǂݍ��߂Ȃ���: " << path << "\n";
		OutputDebugString(ss.str().c_str());
		delete(gh);
		gh = nullptr;
		return nullptr;
	}
	ghs[path] = gh;	//�ǂݍ��߂���ghs�ɒǉ�
	//�����Ԃ�
	return gh;
}

std::vector<int*> ImageManager::LoadAndGetImages(std::vector<std::string> pathes)
{
	std::vector<int*> ghs;
	for (std::string path : pathes) {
		ghs.emplace_back(LoadAndGetImage(path));
	}
	return ghs;
}

std::unordered_map<std::string, int*> ImageManager::ghs;