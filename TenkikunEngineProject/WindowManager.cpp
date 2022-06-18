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
		//�}�E�X���E�B���h�E�̘g���ɂ���Ȃ�
		if (window->IsPointIn(Input::GetMousePosition().x, Input::GetMousePosition().y)) {
			//������g���K�[�ΏۃE�B���h�E�ɐݒ�
			activeWindow = window;


			//�N���b�N�����Ƃ�
			if (Input::GetMouseButtonDown(Input::MouseCode::Mouse_Left, canUseGameWnd)) {
				//�ЂƂ܂����ׂẴE�B���h�E�̑I��������
				for (Window* targetWindow : GetWindows()) {
					targetWindow->ClearSelectedTriggerRect();
				}

				//�E�B���h�E�O���[�v���O�̃E�B���h�E�O���[�v�Ƃ͈Ⴄ�Ȃ�
				if ((typeid(*window) == typeid(GameWindow)) != canUseGameWnd) {
					//�E�B���h�E���Q�[����ʂȂ�Q�[����ʂ̂ݎg����
					canUseGameWnd = (typeid(*window) == typeid(GameWindow));
				}
			}
		}
	}

	if (typeid(*activeWindow) == typeid(GameWindow) && canUseGameWnd || !(typeid(*activeWindow) == typeid(GameWindow)) && !canUseGameWnd) {
		//�C�x���g�`�F�b�N
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
	}

	return windows;
}

GameWindow* WindowManager::gameWindow = new GameWindow();
HierarchyWindow* WindowManager::hierarchyWindow = new HierarchyWindow();
InspectorWindow* WindowManager::inspectorWindow = new InspectorWindow();

Window* WindowManager::activeWindow = WindowManager::gameWindow;	//�����̓Q�[�����

bool WindowManager::canUseGameWnd = true;	//�ŏ��͎g����

