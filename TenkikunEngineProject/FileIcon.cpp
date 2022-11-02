#include "FileIcon.h"
#include "ImageManager.h"
#include "FontManager.h"
#include "ProjectFileManager.h"
#include "SceneIcon.h"

FileIcon::FileIcon(float startX, float startY, float iconWidth, float iconHeight, float blankWidth, float blankHeight, std::string imageFileName, std::filesystem::path path) : TriggerRect(startX, startY, 2 * blankWidth + iconWidth, 2 * blankHeight + iconHeight + FontManager::systemFont->GetFontHeight(), 1)
{
	iconGH = ImageManager::LoadAndGetImage(imageFileName);	//画像を取得
	this->iconWidth = iconWidth;
	this->iconHeight = iconHeight;
	this->blankWidth = blankWidth;
	this->blankHeight = blankHeight;
	this->path = path;	//対になるファイルのパスをセット
	fileNameRect = new TextBox(startX + blankWidth - overWidth / 2, startY + blankHeight + iconHeight, iconWidth + overWidth, FontManager::systemFont->GetFontHeight(), false, path.filename().string());	//TextBox作成
	//エンターキーを押すと
	fileNameRect->pushEnterEvents.push_back(std::make_pair(fileNameRect->GetEventNo(), [this]() {
		//変えられないようになる
		this->fileNameRect->canChange = false;
		//新しい名前を取得
		std::string newName = this->fileNameRect->GetText();
		//前と同じ名前なら終わり
		if (newName == this->path.filename().string())
			return;
		//TreeFileの名前を変更
		TreeNode* node = WindowManager::projectWindow->treeList->FindNode(this->path.string().substr(ProjectFileManager::assetParentPathName.length()));
		node->SetElement(newName);
		//ファイルの名前を変更
		std::string newFileParentPath = this->path.string().substr(0, this->path.string().length() - this->path.filename().string().length());
		std::filesystem::rename(this->path, newFileParentPath + newName);
		//雲ファイルの名前を変更
		std::filesystem::rename(this->path.string() + ".kumo", newFileParentPath + newName + ".kumo");
		//パスを変える
		this->path = newFileParentPath + newName;
		//loadfile();
	}));

	this->mouseClickDownEvents.push_back(std::make_pair(GetEventNo(), [this]() {
		//クリックしたときに自身を選択中にする
		WindowManager::SetSelectedTriggerRect(this);
	}));

	//右クリックを押したら
	mouseRightClickEvents.push_back(std::make_pair(GetEventNo(), [this](void) {
		//選択対象にする
		WindowManager::SetSelectedTriggerRect(this);

		Vector3 mousePos = Input::GetMousePosition();

		MenuList* menuList0 = new MenuList(mousePos.x, mousePos.y, { "Rename", "Delete", "B", "C" });
		MenuNode* menuNode0_0 = menuList0->FindNode("Rename");
		menuNode0_0->mouseClickDownEvents.insert(menuNode0_0->mouseClickDownEvents.begin(), std::make_pair(menuNode0_0->GetEventNo(), [this]() {
			//変更可能にする
			fileNameRect->canChange = true;
			//クリックしたのと同じ動作を行う
			fileNameRect->mouseClickDownEvents[0].second();
		}));
		MenuNode* menuNode0_1 = menuList0->FindNode("Delete");
		menuNode0_1->mouseClickDownEvents.insert(menuNode0_1->mouseClickDownEvents.begin(), std::make_pair(menuNode0_1->GetEventNo(), [this]() {
			//ファイルが存在するなら
			if (std::filesystem::exists(this->path)) {
				//ファイル(フォルダ)を削除
				std::filesystem::remove_all(this->path);
				//TreeListからも削除
				WindowManager::projectWindow->treeList->Delete(this->path.string().substr(ProjectFileManager::assetParentPathName.length()));

				//雲ファイルもあるなら
				if (std::filesystem::exists(this->path.string() + ".kumo")) {
					//雲ファイル削除
					std::filesystem::remove(this->path.string() + ".kumo");
					//TreeListからも削除
					WindowManager::projectWindow->treeList->Delete(std::string(this->path.string() + ".kumo").substr(ProjectFileManager::assetParentPathName.length()));
				}

				//filePrintの表示更新
				WindowManager::projectWindow->filePrintRect->LoadFoler();

				//ファイルアイコンがシーンアイコンだったら
				if (typeid(this) == typeid(SceneIcon*)) {
					//シーンパスリストから削除
					SceneManager::scenePathes.erase(this->GetFileNameNotExtension());
				}
			}
		}));
		//WindowManagerにセット
		WindowManager::SetMenuList(menuList0);
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

std::string FileIcon::GetFileNameNotExtension()
{
	std::string fileName = path.filename().string();

	return fileName.substr(0, fileName.length() - path.filename().extension().string().length());
}
