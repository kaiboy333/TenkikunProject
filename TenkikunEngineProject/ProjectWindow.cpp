#include "ProjectWindow.h"
#include "TreeNode.h"
#include <filesystem>
#include "Debug.h"
#include "MyString.h"
#include "ProjectFileManager.h"

ProjectWindow::ProjectWindow() : Window(0, 500, 1000, 300)
{

}

void ProjectWindow::Init()
{
	//ツリーリスト作成
	treeList = new TreeList(startX, startY, WindowManager::hierarchyWindow->width, height, this, false, true, ProjectFileManager::assetFilePath.filename().string());

	vector<filesystem::path> pathes;

	pathes.push_back(ProjectFileManager::assetFilePath);

	//ツリーリストにアセットのパスを追加
	SetFileChildrenToTreeList(ProjectFileManager::assetFilePath);

	filePrintRect = new FilePrintRect(WindowManager::hierarchyWindow->width, startY, width - WindowManager::hierarchyWindow->width, height, this);
}

void ProjectWindow::Update()
{
	Window::Update();
}

void ProjectWindow::Draw()
{
	Window::Draw();

	if (treeList) {
		treeList->Draw();
	}

	filePrintRect->Draw();
}

void ProjectWindow::SetFileChildrenToTreeList(std::filesystem::path addPath)
{
	vector<filesystem::path> pathes;

	pathes.push_back(addPath);

	//ツリーリストにアセットのパスを追加
	while (pathes.size() != 0) {
		filesystem::path path = pathes[0];
		pathes.erase(pathes.begin());

		//雲ファイルがなければ作成、読み込み
		ProjectFileManager::CreateAndLoadKumoFile(path);

		//パスがディレクトリだったら
		if (filesystem::is_directory(path)) {
			//ノード作成
			TreeNode* node = new TreeNode(path.filename().string(), treeList, treeList->isFirstOpen);

			//イベントを追加
			node->mouseClickDownEvents.push_back([this, node]() {
				//クリックしたノードから絶対パスを求める
				std::filesystem::path path = std::filesystem::path(ProjectFileManager::assetParentPathName + node->GetPath());
				//現在のパスにさっきのパスを入れる
				ProjectFileManager::currentPath = path;
				//パス内のフォルダ更新
				filePrintRect->LoadFoler();
			});

			//パスがアセットフォルダじゃないなら
			if (path != ProjectFileManager::assetFilePath) {
				//親のパスからアセットの上の部分を除いたものを取得
				string parentPathName = path.parent_path().string().substr(ProjectFileManager::assetParentPathName.length());
				//親ディレクトリの名前があるノードに新しくノードを追加
				treeList->Add(node, treeList->FindNode(MyString::Split(parentPathName, '\\')));
			}

			//子をリストに追加
			for (filesystem::path childPath : filesystem::directory_iterator(path)) {
				pathes.push_back(childPath);
			}
		}
		else {
			//ファイルがシーンファイルなら
			if (ProjectFileManager::GetFileType(path) == ProjectFileManager::FileType::Scene) {
				std::string sceneName = path.filename().string().substr(0, path.filename().string().length() - path.extension().string().length());
				//シーンのマップに無かったら
				if (!SceneManager::scenePathes.contains(sceneName)) {
					//シーンマネージャーのリストに追加
					SceneManager::scenePathes.insert(std::make_pair(sceneName, path));
				}
			}
		}
	}
}
