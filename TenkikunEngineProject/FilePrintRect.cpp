#include "FilePrintRect.h"
#include "ProjectFileManager.h"
#include "WindowManager.h"
#include "MyString.h"
#include "Debug.h"

FilePrintRect::FilePrintRect(float startX, float startY, float width, float height, Window* parentWindow) : TriggerRect(startX, startY, width, height, parentWindow)
{
	iconBetweenWidth = (parentWindow->width - iconWidthHeight * maxFileNumInRow) / (maxFileNumInRow + 1);

	DragFileInfoClear();	//ドロップファイル情報の初期化
	SetAlwaysRunFlag(true);		//バックグラウンドでも動作を継続
	SetDragFileValidFlag(true);		//ドラッグアンドドロップを許可

	//ファイルがドロップされたら
	fileDropEvents.push_back([this]() {
		for (std::filesystem::path path : ProjectFileManager::dragFilePathes) {
			DropFileCheck(path);	//ファイルのチェック
		}
	});
}

void FilePrintRect::Draw()
{
	//描画範囲制限
	SetDrawArea(startX, startY, startX + width - 1, startY + height - 1);

	//現在のファイルパス描画
	DrawStringF(startX, startY, ProjectFileManager::currentPath.string().c_str(), GetColor(0, 0, 0));

	//ファイルアイコンの描画
	for (FileIcon* fileIcon : fileIcons) {
		fileIcon->IconDraw();
	}
}

void FilePrintRect::DropFileCheck(std::filesystem::path path)
{
	//パスの拡張子を取得
	std::string extensionName = path.extension().string();

	//現在のパスを取得してペーストしたいパスを作成
	std::filesystem::path pastePath = ProjectFileManager::currentPath.string() + "\\" + path.filename().string();

	//ファイルが存在しないなら
	if (!std::filesystem::exists(pastePath)) {
		//画像の拡張子なら
		if (extensionName == ".png" || extensionName == ".jpg") {
			int iconNum = fileIcons.size();
			//何行何列目に作るか計算する
			int row = iconNum / maxFileNumInRow;
			int col = iconNum % maxFileNumInRow;
			//ファイルをコピーして現在のパスにペースト
			std::filesystem::copy_file(path, pastePath);
			//画像のアイコン作成
			FileIcon* fileIcon = new FileIcon(startX + (col + 1) * iconBetweenWidth + col * iconWidthHeight, startY + (row + 1) * iconBetweenWidth + row * iconWidthHeight, iconWidthHeight, iconWidthHeight, parentWindow, std::filesystem::relative(pastePath).string(), pastePath);
			fileIcons.push_back(fileIcon);
		}
	}

}
