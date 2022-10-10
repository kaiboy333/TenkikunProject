#pragma once
#include "ScrollRect.h"
#include <filesystem>
#include "FileIcon.h"
#include <string>

class TextRect;
class FilePrintRect :  public ScrollRect
{
	public:
		float iconWidthHeight = 50;	//表示するアイコンの幅、高さ
		const int maxFileNumInRow = 8;	//行に表示できる最大のファイルの数
		float iconBetweenWidth;	//アイコン同士の空白の幅

		std::vector<FileIcon*> fileIcons;	//ファイルアイコンたち

		TextRect* pathNameRect = nullptr;	//現在のパスの名前のTextRect

		FilePrintRect(float startX, float startY, float width, float height);

		void Draw();

		void LoadFoler();	//現在のパスを読み込み中身を更新

		virtual void PreparationLibrate() override;

	private:
		void MakeDuplicatedFile(std::filesystem::path copyPath);	//ドロップされたファイルを指定パス作成
};

