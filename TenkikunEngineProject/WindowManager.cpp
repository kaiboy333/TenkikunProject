#include "WindowManager.h"

void WindowManager::Draw()
{
	for (Window* window : GetWindows()) {
		window->Draw();
	}
}

void WindowManager::Update()
{
	for (Window* window : GetWindows()) {
		//マウスがウィンドウの枠内にあるなら
		if (window->IsPointIn(Input::GetMousePosition().x, Input::GetMousePosition().y)) {
			//それをトリガー対象ウィンドウに設定
			activeWindow = window;


			//クリックしたとき
			if (Input::GetMouseButtonDown(Input::MouseCode::Mouse_Left, canUseGameWnd)) {
				//ひとまずすべてのウィンドウの選択を解除
				for (Window* targetWindow : GetWindows()) {
					targetWindow->ClearSelectedTriggerRect();
				}

				//ウィンドウグループが前のウィンドウグループとは違うなら
				if ((typeid(*window) == typeid(GameWindow)) != canUseGameWnd) {
					//ウィンドウがゲーム画面ならゲーム画面のみ使える
					canUseGameWnd = (typeid(*window) == typeid(GameWindow));
				}
			}
		}
	}

	if (typeid(*activeWindow) == typeid(GameWindow) && canUseGameWnd || !(typeid(*activeWindow) == typeid(GameWindow)) && !canUseGameWnd) {
		//イベントチェック
		activeWindow->EventCheck();
	}

	for (Window* window : GetWindows()) {
		window->Update();
	}
}

vector<Window*> WindowManager::GetWindows()
{
	vector<Window*> windows;

	if (gameWindow && hierarchyWindow && inspectorWindow) {
		windows.push_back(gameWindow);
		windows.push_back(hierarchyWindow);
		windows.push_back(inspectorWindow);
		windows.push_back(projectWindow);
	}

	return windows;
}

WindowManager::WindowManager()
{
	gameWindow = new GameWindow();
	hierarchyWindow = new HierarchyWindow();
	inspectorWindow = new InspectorWindow();
	projectWindow = new ProjectWindow();
	projectWindow->Init();

	activeWindow = gameWindow;	//初期はゲーム画面
}

GameWindow* WindowManager::gameWindow = nullptr;
HierarchyWindow* WindowManager::hierarchyWindow = nullptr;
InspectorWindow* WindowManager::inspectorWindow = nullptr;
ProjectWindow* WindowManager::projectWindow = nullptr;

Window* WindowManager::activeWindow = nullptr;	//初期はゲーム画面

bool WindowManager::canUseGameWnd = true;	//最初は使える

