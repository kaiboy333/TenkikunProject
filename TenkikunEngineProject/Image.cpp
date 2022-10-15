#include "Image.h"
#include "ImageManager.h"

Image::Image(std::filesystem::path path) : Info(path, false)	//�������߂Ȃ�
{
	this->gh = ImageManager::LoadAndGetImage(path);	//�摜�ǂݍ���
	if (gh) {
		GetGraphSizeF(gh, &width, &height);	//�摜�T�C�Y�擾
	}
	//ImageManager�̃}�b�v�ɒǉ�
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
