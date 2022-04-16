#pragma once

#include <iostream>
#include "DxLib.h"
#include <unordered_map>

//画像管理クラス
class ImageManager
{
	public:
		static std::unordered_map<std::string, int*> ghs;	//画像ファイルに対応したGraphicHandleを記録したもの

		static int* LoadImage(std::string path);	//画像に対応するGraphicHandleを返す、または作成して返す関数
};

