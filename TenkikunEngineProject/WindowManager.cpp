#include "WindowManager.h"
#include "Debug.h"
#include "ProjectFileManager.h"
#include "FilePrintRect.h"

void WindowManager::Draw()
{
	//画面全体を黒で描画
	DrawBoxAA(0, 0, WIDTH, HEIGHT, GetColor(0, 0, 0), TRUE);

	for (Window* parentWindow : GetWindows()) {
		parentWindow->Draw();
	}
}

void WindowManager::Update()
{
	for (Window* parentWindow : GetWindows()) {
		//クリックしたとき
		if (Input::GetMouseButtonDown(Input::MouseCode::Mouse_Left, canUseGameWnd)) {
			//ひとまず選択を解除
			ClearSelectedTriggerRect();
				

			////ウィンドウグループが前のウィンドウグループとは違うなら
			//if ((typeid(*parentWindow) == typeid(GameWindow)) != canUseGameWnd) {
			//	//ウィンドウがゲーム画面ならゲーム画面のみ使える
			//	canUseGameWnd = (typeid(*parentWindow) == typeid(GameWindow));
			//}
		}
	}

	//if (typeid(*activeWindow) == typeid(GameWindow) && canUseGameWnd || !(typeid(*activeWindow) == typeid(GameWindow)) && !canUseGameWnd) {
	if (!canUseGameWnd) {
		//イベントチェック
		EventCheck();
	}
	//}

	for (Window* parentWindow : GetWindows()) {
		parentWindow->Update();
	}

	//Ctrl + Sを押したら
	if (Input::GetKey(Input::KeyCode::LEFT_CONTROL, false) && Input::GetKeyDown(Input::KeyCode::S, false)) {
		//シーンをセーブ
		SceneManager::SaveScene();
	}
	//Ctrl + Fを押したら
	if (Input::GetKey(Input::KeyCode::LEFT_CONTROL, false) && Input::GetKeyDown(Input::KeyCode::F, false)) {
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
	}
}

vector<Window*> WindowManager::GetWindows()
{
	vector<Window*> windows;

	if (gameWindow && hierarchyWindow && inspectorWindow && projectWindow) {
		windows.push_back(gameWindow);
		windows.push_back(hierarchyWindow);
		windows.push_back(inspectorWindow);
		windows.push_back(projectWindow);
	}

	return windows;
}

WindowManager::WindowManager() : Rect(0, 0, WIDTH, HEIGHT)
{
	gameWindow = new GameWindow();
	hierarchyWindow = new HierarchyWindow();
	inspectorWindow = new InspectorWindow();
	projectWindow = new ProjectWindow();
	projectWindow->Init();

	//activeWindow = gameWindow;	//初期はゲーム画面
}

void WindowManager::SetSelectedTriggerRect(TriggerRect* selectedTriggerRect)
{
	//新しいのをセット
	WindowManager::selectedTriggerRect = selectedTriggerRect;
}

void WindowManager::ClearSelectedTriggerRect()
{
	WindowManager::selectedTriggerRect = nullptr;
}

TriggerRect* WindowManager::GetSelectedTriggerRect()
{
	return selectedTriggerRect;
}

void WindowManager::EventCheck()
{
	//TriggerRectのイベント発生
	for (TriggerRect* triggerRect : triggerRects) {
		triggerRect->CheckInput();	//イベントチェック
	}

	if ((int)activeEvents.size() != 0) {
		//昇順にソート
		std::sort(activeEvents.begin(), activeEvents.end(), [](const std::pair<int, std::function<void()>>& a, const std::pair<int, std::function<void()>>& b)
			{
				return a.first > b.first;
			});

		int activeEventNo = activeEvents.begin()->first;	//実際に実行する番号を記憶

		for (std::pair<int, std::function<void()>> activeEvent : activeEvents) {
			//番号が同じだったなら
			if (activeEvent.first == activeEventNo) {
				activeEvent.second();	//イベントを実行する
			}
			else {
				//終わり
				break;
			}
		}
		activeEvents.clear();	//リストを初期化
	}
}

void WindowManager::RemoveTriggerRect(TriggerRect* triggerRect)
{
	//何か入っているなら
	if (triggerRects.size() != 0) {
		//要素が存在するなら
		if (*std::find(triggerRects.begin(), triggerRects.end(), triggerRect) == triggerRect) {
			triggerRects.erase(remove(triggerRects.begin(), triggerRects.end(), triggerRect));	//実際に削除
		}
	}
}

void WindowManager::AddTriggerRect(TriggerRect* triggerRect)
{
	triggerRects.push_back(triggerRect);	//実際に追加
}

GameWindow* WindowManager::gameWindow = nullptr;
HierarchyWindow* WindowManager::hierarchyWindow = nullptr;
InspectorWindow* WindowManager::inspectorWindow = nullptr;
ProjectWindow* WindowManager::projectWindow = nullptr;

//Window* WindowManager::activeWindow = nullptr;	//初期はゲーム画面

bool WindowManager::canUseGameWnd = false;	//ゲーム画面を操作中か

const float WindowManager::WIDTH = 1300;
const float WindowManager::HEIGHT = 800;

std::vector<std::pair<int, std::function<void()>>> WindowManager::activeEvents;
std::vector<TriggerRect*> WindowManager::triggerRects;	//反応する四角たち
TriggerRect* WindowManager::selectedTriggerRect;	//選択中のTriggerRect
