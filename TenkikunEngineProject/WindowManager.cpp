#include "WindowManager.h"
#include "Debug.h"
#include "ProjectFileManager.h"
#include "FilePrintRect.h"

void WindowManager::Draw()
{
	//��ʑS�̂����ŕ`��
	DrawBoxAA(0, 0, WIDTH, HEIGHT, GetColor(0, 0, 0), TRUE);

	//Window�̕`��
	for (Window* parentWindow : GetWindows()) {
		parentWindow->Draw();
	}

	if (menuList) {
		//���j���[���X�g�̕`��
		menuList->Draw();
	}
}

void WindowManager::Update()
{
	for (Window* parentWindow : GetWindows()) {
		parentWindow->Update();
	}

	//�N���b�N�����Ƃ�
	if (Input::GetMouseButtonDown(Input::MouseCode::Mouse_Left, false)) {
		//�ЂƂ܂��I��������
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
		//�C�x���g�`�F�b�N
		EventCheck();
	}

	//Ctrl + S����������
	if (Input::GetKey(Input::KeyCode::LEFT_CONTROL, false) && Input::GetKeyDown(Input::KeyCode::S, false)) {
		//�V�[�����Z�[�u
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

	//activeWindow = gameWindow;	//�����̓Q�[�����
}

void WindowManager::SetSelectedTriggerRect(TriggerRect* selectedTriggerRect)
{
	//�V�����̂��Z�b�g
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
	//TriggerRect�̃C�x���g����
	for (TriggerRect* triggerRect : triggerRects) {
		triggerRect->CheckInput();	//�C�x���g�`�F�b�N
	}

	if ((int)activeEvents.size() != 0) {
		//�����Ƀ\�[�g
		std::sort(activeEvents.begin(), activeEvents.end(), [](const std::pair<int, std::function<void()>>& a, const std::pair<int, std::function<void()>>& b){
			return a.first > b.first;
		});

		int activeEventNo = activeEvents.begin()->first;	//���ۂɎ��s����ԍ����L��

		for (std::pair<int, std::function<void()>> activeEvent : activeEvents) {
			//�ԍ��������������Ȃ�
			if (activeEvent.first == activeEventNo) {
				activeEvent.second();	//�C�x���g�����s����
			}
			else {
				//�I���
				break;
			}
		}
		activeEvents.clear();	//���X�g��������
	}
}

void WindowManager::SetMenuList(MenuList* menuList)
{
	//�O�̂�����Ȃ�
	if (WindowManager::menuList) {
		//�O�̉������
		WindowManager::menuList->PreparationLibrate();
		//���
		delete(WindowManager::menuList);
		MenuNode::selectedMenuNode = nullptr;
	}
	//�V�����̂��Z�b�g
	WindowManager::menuList = menuList;
}

MenuList* WindowManager::GetMenuList()
{
	return menuList;
}

void WindowManager::RemoveTriggerRect(TriggerRect* triggerRect)
{
	//���������Ă���Ȃ�
	if (triggerRects.size() != 0) {
		//�v�f�����݂���Ȃ�
		if (*std::find(triggerRects.begin(), triggerRects.end(), triggerRect) == triggerRect) {
			triggerRects.erase(remove(triggerRects.begin(), triggerRects.end(), triggerRect));	//���ۂɍ폜
		}
	}
}

void WindowManager::AddTriggerRect(TriggerRect* triggerRect)
{
	triggerRects.push_back(triggerRect);	//���ۂɒǉ�
}

GameWindow* WindowManager::gameWindow = nullptr;
HierarchyWindow* WindowManager::hierarchyWindow = nullptr;
InspectorWindow* WindowManager::inspectorWindow = nullptr;
ProjectWindow* WindowManager::projectWindow = nullptr;

//Window* WindowManager::activeWindow = nullptr;	//�����̓Q�[�����

bool WindowManager::canUseGameWnd = false;	//�Q�[����ʂ𑀍쒆��

const float WindowManager::WIDTH = 1300;
const float WindowManager::HEIGHT = 800;

std::vector<std::pair<int, std::function<void()>>> WindowManager::activeEvents;
std::vector<TriggerRect*> WindowManager::triggerRects;	//��������l�p����
TriggerRect* WindowManager::selectedTriggerRect = nullptr;	//�I�𒆂�TriggerRect
MenuList* WindowManager::menuList = nullptr;	//���ꂽ���j���[���X�g
