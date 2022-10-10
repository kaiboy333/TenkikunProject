#include "FileIcon.h"
#include "ImageManager.h"
#include "FontManager.h"
#include "ProjectFileManager.h"

FileIcon::FileIcon(float startX, float startY, float iconWidth, float iconHeight, float blankWidth, float blankHeight, std::string imageFileName, std::filesystem::path path) : TriggerRect(startX, startY, 2 * blankWidth + iconWidth, 2 * blankHeight + iconHeight + FontManager::systemFont->GetFontHeight())
{
	iconGH = ImageManager::LoadAndGetImage(imageFileName);	//画像を取得
	this->iconWidth = iconWidth;
	this->iconHeight = iconHeight;
	this->blankWidth = blankWidth;
	this->blankHeight = blankHeight;
	this->path = path;	//対になるファイルのパスをセット
	fileNameRect = new TextBox(startX + blankWidth - overWidth / 2, startY + blankHeight + iconHeight, iconWidth + overWidth, FontManager::systemFont->GetFontHeight(), false, path.filename().string());	//TextBox作成

	this->mouseClickDownEvents.push_back(std::make_pair(GetEventNo(), [this]() {
		//クリックしたときに自身を選択中にする
		WindowManager::SetSelectedTriggerRect(this);
	}));
}

void FileIcon::Draw()
{
	if (iconGH) {
		int imageWidth, imageHeight;
		GetGraphSize(iconGH, &imageWidth, &imageHeight);

		if (!GetIsSelected() && GetIsTopOn()) {
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
			//画像のアルファ値を戻す
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		}
	}
}

const float FileIcon::overWidth = 15;

void FileIcon::PreparationLibrate()
{
	//TextBoxの準備、解放
	fileNameRect->PreparationLibrate();
	delete(fileNameRect);
	fileNameRect = nullptr;

	//自身の準備
	TriggerRect::PreparationLibrate();
}
