#pragma once

#include "Image.h"
#include <unordered_map>
#include <filesystem>

//画像管理クラス
class ImageManager
{
	public:
		//static std::unordered_map<std::filesystem::path, Image*> imagePathes;	//画像ファイルパスたち

		static int LoadAndGetImage(std::filesystem::path path);	//画像に対応するGraphicHandleを返す、または作成して返す関数

		static std::vector<int> LoadAndGetImages(std::vector<std::string> pathes);	//画像に対応するGraphicHandleを返す、または作成して返す関数(複数)

		ImageManager();
};



