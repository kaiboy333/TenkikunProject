#include "Image.h"
#include "ImageManager.h"

Image::Image(std::filesystem::path path) {
	this->path = path;	//パスを入れる
	this->gh = ImageManager::LoadAndGetImage(path);	//画像読み込み
	if (gh) {
		GetGraphSizeF(gh, &width, &height);	//画像サイズ取得
	}
	//ImageManagerのマップに追加
	//ImageManager::imagePathes.insert(std::make_pair(path, this));
}

int Image::GetGH()
{
	return gh;
}

float Image::GetWidth()
{
	return width;
}

float Image::GetHeight()
{
	return height;
}

void Image::SetAlpha(int alpha)
{
	this->alpha = (int)MyMath::Clamp((float)alpha, 0, 255);
}

int Image::GetAlpha()
{
	return alpha;
}

std::filesystem::path Image::GetPath()
{
	return path;
}
