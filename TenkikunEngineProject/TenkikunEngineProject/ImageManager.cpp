#include "ImageManager.h"

int* ImageManager::LoadImage(std::string path)
{
	//もし、既に画像が読み込まれていたなら
	if (ghs.count(path.c_str())) {
		return ghs[path.c_str()];	//それを返す
	}

	//画像を新しく読み込む
	int gh;		//GraphicHandle
	//画像が読み込めなかったら
	if ((gh = LoadGraph(path.c_str()) == -1)) {
		std::cout << "画像ファイルが読み込めないよ" << std::endl;
		return nullptr;
	}
	ghs[path] = &gh;	//読み込めたらghsに追加
	//それを返す
	return &gh;
}
