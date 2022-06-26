#include "FilePrintRect.h"

FilePrintRect::FilePrintRect(float startX, float startY, float width, float height, Window* parentWindow) : TriggerRect(startX, startY, width, height, parentWindow)
{
	DragFileInfoClear();	//ドロップファイル情報の初期化
	SetAlwaysRunFlag(true);		//バックグラウンドでも動作を継続
	SetDragFileValidFlag(true);		//ドラッグアンドドロップを許可

	//ファイルがドロップされたら
	fileDropEvents.push_back([this]() {
		TCHAR currentPath[100] = {};
		//ファイルが読み込めたら
		if (GetDragFilePath(currentPath) != -1) {
			//this->currentPath = currentPath;	//パスを記憶
		}
		else {
			//this->currentPath = "";
		}
	});

}

void FilePrintRect::Draw()
{
	//DrawStringF(startX, startY + height / 2, currentPath.filename().string().c_str(), GetColor(0, 0, 0));
}
