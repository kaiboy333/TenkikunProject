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
		//画像のアルファ値設定
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

		//ファイル名の描画
		fileNameRect->Draw();

		//画像の描画
		DrawRotaGraph3F(startX + width / 2, startY + height / 2, imageWidth / 2.0f, imageHeight / 2.0f, width / imageWidth, height / imageHeight, 0, iconGH, TRUE);
		//選択されていたら
		if (GetIsSelected()) {
			//画像のアルファ値設定
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
			//青色を描画
			DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(173, 216, 230), TRUE);
		}
		
		//画像のアルファ値戻す
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
}

const float FileIcon::blankWidth = 10;
const float FileIcon::overWidth = 15;
