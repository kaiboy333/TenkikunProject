#include "FilePrintRect.h"
#include "ProjectFileManager.h"
#include "WindowManager.h"
#include "MyString.h"
#include "Debug.h"
#include "ImageIcon.h"

FilePrintRect::FilePrintRect(float startX, float startY, float width, float height, Window* parentWindow) : ScrollRect(startX, startY, width, height, width, height, parentWindow)
{
	//アイコン同士の空白幅を計算する
	iconBetweenWidth = (width - iconWidthHeight * maxFileNumInRow) / (maxFileNumInRow + 1);

	string pathName = ProjectFileManager::currentPath.string().substr(ProjectFileManager::assetParentPathName.length());	//親のパスからアセットの上の部分を除いたものを取得
	pathNameRect = new TextRect(startX, startY, pathName);		//現在のパスの名前をセット

	//ファイルがドロップされたら
	fileDropEvents.push_back([this]() {
		for (std::filesystem::path path : ProjectFileManager::dragFilePathes) {
			MakeDuplicatedFile(path);	//ファイルを複製して指定のパスに置く
		}
		LoadFoler();	//フォルダ内表示更新
	});

	//パスのフォルダ更新
	LoadFoler();
}

void FilePrintRect::Draw()
{
	//画像のアルファ値設定
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

	//枠描画
	DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(0, 0, 0), FALSE);

	//ファイルアイコンの描画
	for (FileIcon* fileIcon : fileIcons) {
		fileIcon->Draw();
	}

	//画像のアルファ値設定
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

	DrawBoxAA(pathNameRect->startX, pathNameRect->startY, pathNameRect->startX + width, pathNameRect->startY + pathNameRect->height, GetColor(255, 255, 255), TRUE);
	//現在のファイルパス描画
	pathNameRect->Draw();
	DrawBoxAA(pathNameRect->startX, pathNameRect->startY, pathNameRect->startX + width, pathNameRect->startY + pathNameRect->height, GetColor(0, 0, 0), FALSE);
}

void FilePrintRect::MakeDuplicatedFile(std::filesystem::path copyPath)
{
	//現在のパスを取得してペーストしたいパスを作成
	std::filesystem::path pastePath = ProjectFileManager::currentPath.string() + "\\" + copyPath.filename().string();

	//ファイルが存在しないなら
	if (!std::filesystem::exists(pastePath)) {
		//元のファイルタイプを確認して大丈夫そうなら
		if (ProjectFileManager::GetFileType(copyPath) != ProjectFileManager::FileType::None) {
			//ファイルをペースト
			filesystem::copy(copyPath, pastePath);
			//ファイルをチェック
			ProjectFileManager::CheckAddFile(pastePath);
			//ツリーリストにフォルダ名を追加
			WindowManager::projectWindow->SetFileChildrenToTreeList(pastePath);
		}
	}

}

void FilePrintRect::LoadFoler()
{
	//前のアイコンを消去
	for (FileIcon* fileIcon : fileIcons) {
		//parentWindowから削除(アイコン)
		parentWindow->RemoveTriggerRect(fileIcon);
		//parentWindowから削除(TextBox)
		parentWindow->RemoveTriggerRect(fileIcon->fileNameRect);
		//スクロールのリストからも削除
		RemoveToScrollRect(fileIcon);
		//アイコンにあるTextBoxも削除
		RemoveToScrollRect(fileIcon->fileNameRect);
	}
	//リストをリセット
	fileIcons.clear();

	//スクロールのリセット
	InitScrollPos();


	//現在のパスの名前をセット
	string pathName = ProjectFileManager::currentPath.string().substr(ProjectFileManager::assetParentPathName.length());	//親のパスからアセットの上の部分を除いたものを取得
	pathNameRect = new TextRect(startX, startY, pathName);		//現在のパスの名前をセット

	//パスがディレクトリだったら
	if (filesystem::is_directory(ProjectFileManager::currentPath)) {
		int iconNum = 0;
		//中身を参照
		for (filesystem::path childPath : filesystem::directory_iterator(ProjectFileManager::currentPath)) {
			//何行何列目に作るか計算する
			int row = iconNum / maxFileNumInRow;
			int col = iconNum % maxFileNumInRow;

			//ファイルタイプをチェックしてそれぞれの処理をする(主にアイコンを作成)
			FileIcon* fileIcon = nullptr;
			float iconStartX = startX + (col + 1) * iconBetweenWidth + col * iconWidthHeight;
			float iconStartY = startY + (row + 1) * iconBetweenWidth + row * iconWidthHeight;
			switch (ProjectFileManager::GetFileType(childPath)) {
				case ProjectFileManager::FileType::Image:
					//イメージアイコン作成
					fileIcon = new ImageIcon(iconStartX, iconStartY, iconWidthHeight, iconWidthHeight, 10, 5, parentWindow, std::filesystem::relative(childPath).string(), childPath);
					break;
				case ProjectFileManager::FileType::Folder:
					//フォルダアイコン作成
					fileIcon = new FileIcon(iconStartX, iconStartY, iconWidthHeight, iconWidthHeight, 10, 5, parentWindow, ProjectFileManager::imageFilePath.string() + "\\folder.png", childPath);
					break;
				case ProjectFileManager::FileType::Script_cpp:
					//スクリプト(cpp)アイコン作成
					fileIcon = new FileIcon(iconStartX, iconStartY, iconWidthHeight, iconWidthHeight, 10, 5, parentWindow, ProjectFileManager::imageFilePath.string() + "\\script_cpp.png", childPath);
					break;
				case ProjectFileManager::FileType::Script_hpp:
					//スクリプト(hpp)アイコン作成
					fileIcon = new FileIcon(iconStartX, iconStartY, iconWidthHeight, iconWidthHeight, 10, 5, parentWindow, ProjectFileManager::imageFilePath.string() + "\\script_hpp.png", childPath);
					break;
				case ProjectFileManager::FileType::Script_h:
					//スクリプト(h)アイコン作成
					fileIcon = new FileIcon(iconStartX, iconStartY, iconWidthHeight, iconWidthHeight, 10, 5, parentWindow, ProjectFileManager::imageFilePath.string() + "\\script_h.png", childPath);
					break;
				case ProjectFileManager::FileType::Scene:
					//シーンアイコン作成
					fileIcon = new FileIcon(iconStartX, iconStartY, iconWidthHeight, iconWidthHeight, 10, 5, parentWindow, ProjectFileManager::imageFilePath.string() + "\\Tenkikun.png", childPath);
					break;
				case ProjectFileManager::FileType::None:
					//何もしない
					break;
			}

			//ファイルアイコンが作成されているなら
			if (fileIcon) {
				//Scrollのリストにアイコンを追加(&更新)
				AddToScrollRect(fileIcon);
				//アイコンにあるTextBoxも登録
				AddToScrollRect(fileIcon->fileNameRect);
				//リストに追加
				fileIcons.push_back(fileIcon);
				//次の番号へ
				iconNum++;
			}

		}
	}

	int row = (int)fileIcons.size() / maxFileNumInRow;
	if ((int)fileIcons.size() % maxFileNumInRow != 0) {
		row++;
	}
	scrollHeight = (row + 1) * iconBetweenWidth + row * (iconWidthHeight + FileIcon::overWidth);
	ScrollUpdate();
}
