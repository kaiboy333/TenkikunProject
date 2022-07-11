#pragma once

#include <DxLib.h>
#include "FileIcon.h"
#include "MyMath.h"
#include "Info.h"

class Image : public Info
{
	public:
		Image(std::filesystem::path path);

		int GetGH();	//グラフィックハンドル取得(Stateで使う)

		float GetWidth();	//横幅取得
		float GetHeight();	//縦幅取得

		void SetAlpha(int alpha);
		int GetAlpha();

		std::filesystem::path GetPath();

	private:
		int gh = -1;

		float width, height;	//横幅、縦幅

		int alpha = 255;	//画像のアルファ値

		std::filesystem::path path;	//画像のパス
};

