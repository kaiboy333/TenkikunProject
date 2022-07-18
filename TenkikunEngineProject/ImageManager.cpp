#include "ImageManager.h"
#include "Debug.h"

ImageManager::ImageManager() {

}

int ImageManager::LoadAndGetImage(std::filesystem::path path)
{
	////�����A���ɉ摜���ǂݍ��܂�Ă����Ȃ�
	//if (ghs.count(path.c_str())) {
	//	return ghs[path.c_str()];	//�����Ԃ�
	//}

	//�摜��V�����ǂݍ���
	int gh;		//GraphicHandle
	gh = LoadGraph(path.string().c_str());
	//�摜���ǂݍ��߂Ȃ�������
	if (gh == -1) {
		Debug::Log("�摜�t�@�C�����ǂݍ��߂Ȃ���: " + path.string());
	}
	//�����Ԃ�
	return gh;
}

std::vector<int> ImageManager::LoadAndGetImages(std::vector<std::string> pathes)
{
	std::vector<int> ghs;
	for (std::string path : pathes) {
		ghs.emplace_back(LoadAndGetImage(path));
	}
	return ghs;
}