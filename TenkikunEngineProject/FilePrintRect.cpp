#include "FilePrintRect.h"
#include "ProjectFileManager.h"
#include "WindowManager.h"
#include "MyString.h"
#include "Debug.h"

FilePrintRect::FilePrintRect(float startX, float startY, float width, float height, Window* parentWindow) : TriggerRect(startX, startY, width, height, parentWindow)
{
	iconBetweenWidth = (parentWindow->width - iconWidthHeight * maxFileNumInRow) / (maxFileNumInRow + 1);

	//ファイルがドロップされたら
	fileDropEvents.push_back([this]() {
		for (std::filesystem::path path : ProjectFileManager::dragFilePathes) {
			MakeDuplicatedFile(path);	//ファイルを複製して指定のパスに置く
		}
	});

	//パスのフォルダ更新
	LoadFoler();
}

void FilePrintRect::Draw()
{
	//描画範囲制限
	SetDrawArea(startX, startY, startX + width, startY + height);

	//枠描画
	DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(0, 0, 0), FALSE);

	//現在のファイルパス描画
	DrawStringF(startX, startY, ProjectFileManager::currentPath.string().c_str(), GetColor(0, 0, 0));

	//ファイルアイコンの描画
	for (FileIcon* fileIcon : fileIcons) {
		fileIcon->IconDraw();
	}
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
			//ツリーリストにフォルダ名を追加
			WindowManager::projectWindow->SetFileChildrenToTreeList(pastePath);
			//フォルダ内表示更新
			LoadFoler();
		}
	}

}

void FilePrintRect::LoadFoler()
{
	//前のアイコンを消去
	for (FileIcon* fileIcon : fileIcons) {
		//parentWindowから削除
		parentWindow->RemoveTriggerRect(fileIcon);
	}
	//リストをリセット
	fileIcons.clear();

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
				fileIcon = new FileIcon(iconStartX, iconStartY, iconWidthHeight, iconWidthHeight, parentWindow, std::filesystem::relative(childPath).string(), childPath);
				break;
			case ProjectFileManager::FileType::Folder:
				//フォルダアイコン作成
				fileIcon = new FileIcon(iconStartX, iconStartY, iconWidthHeight, iconWidthHeight, parentWindow, "image\\folder.png", childPath);
				break;
			case ProjectFileManager::FileType::Script:
				//スクリプトアイコン作成
				fileIcon = new FileIcon(iconStartX, iconStartY, iconWidthHeight, iconWidthHeight, parentWindow, "image\\script.png", childPath);
				break;
			case ProjectFileManager::FileType::None:
				//何もしない
				break;
			}

			//ファイルアイコンが作成されているなら
			if (fileIcon) {
				//リストに追加
				fileIcons.push_back(fileIcon);
				//次の番号へ
				iconNum++;
			}

		}
	}
}
