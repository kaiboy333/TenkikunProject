#include "FileIcon.h"
#include "ImageManager.h"
#include "FontManager.h"

FileIcon::FileIcon(float startX, float startY, float iconWidth, float iconHeight, float blankWidth, float blankHeight, Window* parentWindow, std::string imageFileName, std::filesystem::path path) : TriggerRect(startX, startY, 2 * blankWidth + iconWidth, 2 * blankHeight + iconHeight + FontManager::systemFont->GetFontHeight(), parentWindow)
{
	iconGH = ImageManager::LoadAndGetImage(imageFileName);	//画像を取得
	this->iconWidth = iconWidth;
	this->iconHeight = iconHeight;
	this->blankWidth = blankWidth;
	this->blankHeight = blankHeight;
	this->path = path;	//対になるファイルのパスをセット
	fileNameRect = new TextBox(startX + blankWidth - overWidth / 2, startY + blankHeight + iconHeight, iconWidth + overWidth, FontManager::systemFont->GetFontHeight(), parentWindow, false, path.filename().string());	//TextBox作成

	this->mouseClickDownEvents.push_back([this]() {
		//クリックしたときに自身を選択中にする
		this->parentWindow->SetSelectedTriggerRect(this);
	});
}

void FileIcon::Draw()
{
	if (iconGH) {
		int imageWidth, imageHeight;
		GetGraphSize(iconGH, &imageWidth, &imageHeight);

		//画像のアルファ値設定
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

		if (!GetIsSelected() && isOn) {
			//灰色を描画
			DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(200, 200, 200), TRUE);
		}

		if (isImageIcon) {
			//アイコン後ろの四角を描画(アイコン背景)
			DrawBoxAA(startX + blankWidth, startY + blankHeight, startX + blankWidth + iconWidth, startY + blankHeight + iconHeight, GetColor(100, 100, 100), TRUE);
		}

		//ファイル名の描画
		fileNameRect->Draw();

		//画像の描画
		DrawRotaGraph3F(startX + blankWidth + iconWidth / 2, startY + blankHeight + iconHeight / 2, imageWidth / 2.0f, imageHeight / 2.0f, iconWidth / imageWidth, iconHeight / imageHeight, 0, iconGH, TRUE);

		//選択されていたら
		if (GetIsSelected()) {
			//画像のアルファ値設定
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
			//青色を描画
			DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(30, 144, 255), TRUE);
		}
		
		//画像のアルファ値戻す
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
}

const float FileIcon::overWidth = 15;