#pragma once

#include <iostream>
#include "ImageManager.h"
#include <DxLib.h>
#include "FileIcon.h"
#include "MyMath.h"
#include "Info.h"

class Image : public Info
{
	public:
		Image(std::string path);

		int GetGH();	//グラフィックハンドル取得(Stateで使う)

		float GetWidth();	//横幅取得
		float GetHeight();	//縦幅取得

		void SetAlpha(int alpha);
		int GetAlpha();

	private:
		int gh = -1;

		float width, height;	//横幅、縦幅

		int alpha = 255;	//画像のアルファ値

		std::string path;	//画像のパス
};

inline Image::Image(std::string path) {
	this->path = path;	//パスを入れる
	this->gh = ImageManager::LoadAndGetImage(path);	//画像読み込み
	if (gh) {
		GetGraphSizeF(gh, &width, &height);	//画像サイズ取得
	}
}

inline int Image::GetGH()
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

inline void Image::SetAlpha(int alpha)
{
	this->alpha = (int)MyMath::Clamp((float)alpha, 0, 255);
}

inline int Image::GetAlpha()
{
	return alpha;
}


