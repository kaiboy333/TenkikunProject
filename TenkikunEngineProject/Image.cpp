#include "Image.h"
#include "ImageManager.h"

Image::Image(std::filesystem::path path) : Info(path, false)	//書き込めない
{
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

void Image::PreparationLibrate()
{

}
