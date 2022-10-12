#include "WindowManager.h"
#include "Debug.h"
#include "ProjectFileManager.h"
#include "FilePrintRect.h"

void WindowManager::Draw()
{
	//画面全体を黒で描画
	DrawBoxAA(0, 0, WIDTH, HEIGHT, GetColor(0, 0, 0), TRUE);

	//Windowの描画
	for (Window* parentWindow : GetWindows()) {
		parentWindow->Draw();
	}

	if (menuList) {
		//メニューリストの描画
		menuList->Draw();
	}
}

void WindowManager::Update()
{
	for (Window* parentWindow : GetWindows()) {
		parentWindow->Update();
	}

	//クリックしたとき
	if (Input::GetMouseButtonDown(Input::MouseCode::Mouse_Left, false)) {
		//ひとまず選択を解除
		ClearSelectedTriggerRect();
		//return;
	}

	Vector3 mousePos = Input::GetMousePosition();
	bool isOnGameWnd = gameWindow->IsPointIn2(mousePos.x, mousePos.y);

	if (canUseGameWnd && !isOnGameWnd && Input::GetMouseButtonDown(Input::MouseCode::Mouse_Left, true) || !canUseGameWnd && isOnGameWnd && Input::GetMouseButtonDown(Input::MouseCode::Mouse_Left, false)) {
		canUseGameWnd = !canUseGameWnd;
		return;
	}

	if (!canUseGameWnd) {
		//イベントチェック
		EventCheck();
	}

	//Ctrl + Sを押したら
	if (Input::GetKey(Input::KeyCode::LEFT_CONTROL, false) && Input::GetKeyDown(Input::KeyCode::S, false)) {
		//シーンをセーブ
		SceneManager::SaveScene();
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
		std::sort(activeEvents.begin(), activeEvents.end(), [](const std::pair<int, std::function<void()>>& a, const std::pair<int, std::function<void()>>& b){
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

void WindowManager::SetMenuList(MenuList* menuList)
{
	//前のがあるなら
	if (WindowManager::menuList) {
		//前の解放準備
		WindowManager::menuList->PreparationLibrate();
		//解放
		delete(WindowManager::menuList);
		MenuNode::selectedMenuNode = nullptr;
	}
	//新しいのをセット
	WindowManager::menuList = menuList;
}

MenuList* WindowManager::GetMenuList()
{
	return menuList;
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
TriggerRect* WindowManager::selectedTriggerRect = nullptr;	//選択中のTriggerRect
MenuList* WindowManager::menuList = nullptr;	//作られたメニューリスト
