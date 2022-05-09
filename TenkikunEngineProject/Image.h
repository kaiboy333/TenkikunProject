#pragma once

#include <iostream>
#include "ImageManager.h"
#include <DxLib.h>

class Image
{
	public:
		Image(std::string path);

		int* GetGH();	//グラフィックハンドル取得(Stateで使う)

		float GetWidth();	//横幅取得
		float GetHeight();	//縦幅取得

	private:
		int* gh = nullptr;

		float width, height;	//横幅、縦幅

		std::string path;	//画像のパス
};

inline Image::Image(std::string path)
{
	this->path = path;	//パスを入れる
	this->gh = ImageManager::Instance()->LoadAndGetImage(path);	//画像読み込み
	GetGraphSizeF(*gh, &width, &height);	//画像サイズ取得
}

inline int* Image::GetGH()
{
	return gh;
}

inline float Image::GetWidth()
{
	return width;
}

inline float Image::GetHeight()
{
	return height;
}


