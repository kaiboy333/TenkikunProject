#pragma once
#include "TriggerRect.h"
#include <filesystem>
#include "FileIcon.h"
#include <string>

class FilePrintRect :  public TriggerRect
{
	public:
		float iconWidthHeight = 50;	//表示するアイコンの幅、高さ
		int maxFileNumInRow = 10;	//行に表示できる最大のファイルの数
		float iconBetweenWidth;	//アイコン同士の空白の幅

		std::vector<FileIcon*> fileIcons;	//ファイルアイコンたち

		FilePrintRect(float startX, float startY, float width, float height, Window* parentWindow);

		void Draw();

		void LoadFoler();	//現在ののパスを読み込み中身を更新

	private:
		void MakeDuplicatedFile(std::filesystem::path copyPath);	//ドロップされたファイルを指定パス作成
};

