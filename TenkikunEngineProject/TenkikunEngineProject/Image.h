#pragma once
#include "Component.h"
#include "DxLib.h"
#include <iostream>

class Image :  public Component
{
	public:
		bool isFlipX = FALSE;
		bool isFlipY = FALSE;

		void Draw();	//画像を描画

		void SetImage(std::string path);	//ファイルパスからGraphicHandleをセット
		void SetGH(int* gh);	//GraphicHandleをセット

		inline void SetGH(int* gh) {
			this->gh = gh;
		}
	private:
		int* gh = 0;	//グラフィックハンドル
};

