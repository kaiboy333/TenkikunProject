#include "FileIcon.h"
#include "ImageManager.h"
#include "FontManager.h"

FileIcon::FileIcon(float startX, float startY, float width, float height, Window* parentWindow, std::string imageFileName, std::filesystem::path path) : TriggerRect(startX, startY, width, height, parentWindow)
{
	iconGH = ImageManager::LoadAndGetImage(imageFileName);	//画像を取得
	this->path = path;	//対になるファイルのパスをセット
	fileNameRect = new TextBox(startX - overWidth / 2, startY + height, width + overWidth, FontManager::systemFont->GetFontHeight(), parentWindow, false, path.filename().string());	//TextBox作成
}

void FileIcon::Draw()
{
	if (iconGH) {
		int imageWidth, imageHeight;
		GetGraphSize(iconGH, &imageWidth, &imageHeight);
		//画像の描画
		DrawRotaGraph3F(startX + width / 2, startY + height / 2, imageWidth / 2.0f, imageHeight / 2.0f, width / imageWidth, height / imageHeight, 0, iconGH, TRUE);
		//ファイル名の描画
		fileNameRect->Draw();
	}
}
