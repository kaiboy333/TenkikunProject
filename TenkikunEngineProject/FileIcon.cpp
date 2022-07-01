#include "FileIcon.h"
#include "ImageManager.h"
#include "FontManager.h"

FileIcon::FileIcon(float startX, float startY, float width, float height, Window* parentWindow, std::string imageFileName, std::filesystem::path path) : TriggerRect(startX, startY, width, height, parentWindow)
{
	iconGH = ImageManager::LoadAndGetImage(imageFileName);	//画像を取得
	this->path = path;	//対になるファイルのパスをセット
	fileNameRect = new TextBox(startX, startY + height, width, FontManager::systemFont->GetFontHeight(), parentWindow, path.filename().string());	//TextBox作成
}

void FileIcon::IconDraw()
{
	if (iconGH) {
		//アイコン後ろの四角を描画(アイコン背景)
		DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(200, 200, 200), TRUE);

		int imageWidth, imageHeight;
		GetGraphSize(iconGH, &imageWidth, &imageHeight);
		//画像の描画
		DrawRotaGraph3F(startX + width / 2, startY + height / 2, imageWidth / 2.0f, imageHeight / 2.0f, width / imageWidth, height / imageHeight, 0, iconGH, TRUE);
		//ファイル名の描画
		fileNameRect->Draw();
	}
}
