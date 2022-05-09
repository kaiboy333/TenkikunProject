#pragma once

#include <iostream>
#include <unordered_map>

//画像管理クラス
class ImageManager
{
	public:
		static ImageManager* Instance();	//ここから毎回インスタンスを呼ぶ

		static void Destroy();	//インスタンスを削除(解放)

		std::unordered_map<std::string, int*> ghs;	//画像ファイルに対応したGraphicHandleを記録したもの

		int* LoadAndGetImage(std::string path);	//画像に対応するGraphicHandleを返す、または作成して返す関数

		std::vector<int*> LoadAndGetImages(std::vector<std::string> pathes);	//画像に対応するGraphicHandleを返す、または作成して返す関数(複数)

	private:
		ImageManager();	//インスタンスを普通には生成させない

		static ImageManager* instance;	//ただ一つだけのインスタンス
};



