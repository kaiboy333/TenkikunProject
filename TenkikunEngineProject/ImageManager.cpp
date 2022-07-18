#include "ImageManager.h"
#include "Debug.h"

ImageManager::ImageManager() {

}

int ImageManager::LoadAndGetImage(std::filesystem::path path)
{
	////もし、既に画像が読み込まれていたなら
	//if (ghs.count(path.c_str())) {
	//	return ghs[path.c_str()];	//それを返す
	//}

	//画像を新しく読み込む
	int gh;		//GraphicHandle
	gh = LoadGraph(path.string().c_str());
	//画像が読み込めなかったら
	if (gh == -1) {
		Debug::Log("画像ファイルが読み込めないよ: " + path.string());
	}
	//それを返す
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