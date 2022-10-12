#include "FilePrintRect.h"
#include "ProjectFileManager.h"
#include "WindowManager.h"
#include "MyString.h"
#include "Debug.h"
#include "ImageIcon.h"
#include "FolderIcon.h"
#include "ScriptIcon.h"

FilePrintRect::FilePrintRect(float startX, float startY, float width, float height) : ScrollRect(startX, startY, width, height, width, height)
{
	//アイコン同士の空白幅を計算する
	iconBetweenWidth = (width - iconWidthHeight * maxFileNumInRow) / (maxFileNumInRow + 1);

	string pathName = ProjectFileManager::currentPath.string().substr(ProjectFileManager::assetParentPathName.length());	//親のパスからアセットの上の部分を除いたものを取得
	pathNameRect = new TextRect(startX, startY, pathName);		//現在のパスの名前をセット

	//ファイルがドロップされたら
	fileDropEvents.push_back(std::make_pair(GetEventNo(), [this]() {
		for (std::filesystem::path path : ProjectFileManager::dragFilePathes) {
			MakeDuplicatedFile(path);	//ファイルを複製して指定のパスに置く
		}
	}));

	//右クリックを押したら
	mouseRightClickEvents.push_back(std::make_pair(GetEventNo(), [this]() {
		Vector3 mousePos = Input::GetMousePosition();

		MenuList* menuList0 = new MenuList(mousePos.x, mousePos.y, { "Create", "Delete", "B", "C" });
		//WindowManagerにセット
		WindowManager::SetMenuList(menuList0);

		MenuNode* menuNode0_0 = menuList0->FindNode("Create");
		MenuList* menuList1 = new MenuList(menuNode0_0->startX + menuNode0_0->width, menuNode0_0->startY, { "Folder", "C++ Script" });
		MenuNode* menuNode1_0 = menuList1->FindNode("Folder");
		menuNode1_0->mouseClickDownEvents.insert(menuNode1_0->mouseClickDownEvents.begin(), std::make_pair(menuNode1_0->GetEventNo(), []() {
			//フォルダを作成
			std::filesystem::path folderPath = ProjectFileManager::currentPath.string() + "\\Folder";
			//ファイルが存在しないなら
			if (!std::filesystem::exists(folderPath)) {
				////元のファイルタイプを確認して大丈夫そうなら
				//if (ProjectFileManager::IsFileType(folderPath)) {
					//フォルダを作成
					std::filesystem::create_directory(folderPath);
					//ファイルをチェック
					ProjectFileManager::CheckAddFile(folderPath);
					//ツリーリストにフォルダ名を追加
					WindowManager::projectWindow->SetFileChildrenToTreeList(folderPath);
					//フォルダ内表示更新
					WindowManager::projectWindow->filePrintRect->LoadFoler();
				//}
			}
		}));
		MenuNode* menuNode1_1 = menuList1->FindNode("C++ Script");
		menuNode1_1->mouseClickDownEvents.insert(menuNode1_1->mouseClickDownEvents.begin(), std::make_pair(menuNode1_1->GetEventNo(), []() {
			//スクリプトを作成
			std::vector<std::filesystem::path> scriptPathes;
			//.h
			scriptPathes.push_back(std::filesystem::path(ProjectFileManager::currentPath.string() + "\\Script.h"));
			//.cpp
			scriptPathes.push_back(std::filesystem::path(ProjectFileManager::currentPath.string() + "\\Script.cpp"));
			for (auto& scriptPath : scriptPathes) {
				//ファイルが存在しないなら
				if (!std::filesystem::exists(scriptPath)) {
					//元のファイルタイプを確認して大丈夫そうなら
					if (ProjectFileManager::IsFileType(scriptPath)) {
						//ファイルを作成
						std::ofstream ofs(scriptPath);
						//ファイルをチェック
						ProjectFileManager::CheckAddFile(scriptPath);
						//ツリーリストにフォルダ名を追加
						WindowManager::projectWindow->SetFileChildrenToTreeList(scriptPath);
						//フォルダ内表示更新
						WindowManager::projectWindow->filePrintRect->LoadFoler();
					}
				}
			}
		}));
		//メニューノードにメニューリストをセット
		menuNode0_0->SetChildMenuList(menuList1);
	}));
}

void FilePrintRect::Draw()
{
	//枠描画
	DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(0, 0, 0), FALSE);

	//ファイルアイコンの描画
	for (FileIcon* fileIcon : fileIcons) {
		fileIcon->Draw();
	}

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
		if (ProjectFileManager::IsFileType(copyPath)) {
			//ファイルをペースト
			filesystem::copy(copyPath, pastePath);
			//ファイルをチェック
			ProjectFileManager::CheckAddFile(pastePath);
			//ツリーリストにフォルダ名を追加
			WindowManager::projectWindow->SetFileChildrenToTreeList(pastePath);
			//フォルダ内表示更新
			LoadFoler();
		}
	}

}

void FilePrintRect::PreparationLibrate()
{
	//前のアイコンを消去
	for (FileIcon* fileIcon : fileIcons) {
		//スクロールのリストからも削除
		RemoveToScrollRect(fileIcon);
		//アイコンにあるTextBoxも削除
		RemoveToScrollRect(fileIcon->fileNameRect);
		
		//アイコンの解放準備
		fileIcon->PreparationLibrate();
		//解放
		delete(fileIcon);
		fileIcon = nullptr;
	}
	//リストをリセット
	fileIcons.clear();

	//TextRect解放準備
	pathNameRect->PreparationLibrate();
	//解放
	delete(pathNameRect);
	pathNameRect = nullptr;

}

void FilePrintRect::LoadFoler()
{
	//解放準備(リセット)
	PreparationLibrate();

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
					fileIcon = new ImageIcon(iconStartX, iconStartY, iconWidthHeight, iconWidthHeight, 10, 5, std::filesystem::relative(childPath).string(), childPath);
					break;
				case ProjectFileManager::FileType::Folder:
					//フォルダアイコン作成
					fileIcon = new FolderIcon(iconStartX, iconStartY, iconWidthHeight, iconWidthHeight, 10, 5, ProjectFileManager::imageFilePath.string() + "\\folder.png", childPath);
					break;
				case ProjectFileManager::FileType::Script_cpp:
					//スクリプト(cpp)アイコン作成
					fileIcon = new ScriptIcon(iconStartX, iconStartY, iconWidthHeight, iconWidthHeight, 10, 5, ProjectFileManager::imageFilePath.string() + "\\script_cpp.png", childPath);
					break;
				case ProjectFileManager::FileType::Script_hpp:
					//スクリプト(hpp)アイコン作成
					fileIcon = new ScriptIcon(iconStartX, iconStartY, iconWidthHeight, iconWidthHeight, 10, 5, ProjectFileManager::imageFilePath.string() + "\\script_hpp.png", childPath);
					break;
				case ProjectFileManager::FileType::Script_h:
					//スクリプト(h)アイコン作成
					fileIcon = new ScriptIcon(iconStartX, iconStartY, iconWidthHeight, iconWidthHeight, 10, 5, ProjectFileManager::imageFilePath.string() + "\\script_h.png", childPath);
					break;
				case ProjectFileManager::FileType::Scene:
					//シーンアイコン作成
					fileIcon = new FileIcon(iconStartX, iconStartY, iconWidthHeight, iconWidthHeight, 10, 5, ProjectFileManager::imageFilePath.string() + "\\Tenkikun.png", childPath);
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
