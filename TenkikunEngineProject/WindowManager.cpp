#include "WindowManager.h"
#include "Debug.h"
#include "ProjectFileManager.h"
#include "FilePrintRect.h"

void WindowManager::Draw()
{
	for (Window* parentWindow : GetWindows()) {
		parentWindow->Draw();
	}
}

void WindowManager::Update()
{
	for (Window* parentWindow : GetWindows()) {
		//�}�E�X���E�B���h�E�̘g���ɂ���Ȃ�
		if (parentWindow->IsPointIn2(Input::GetMousePosition().x, Input::GetMousePosition().y)) {
			//������g���K�[�ΏۃE�B���h�E�ɐݒ�
			activeWindow = parentWindow;


			//�N���b�N�����Ƃ�
			if (Input::GetMouseButtonDown(Input::MouseCode::Mouse_Left, canUseGameWnd)) {
				//�ЂƂ܂����ׂẴE�B���h�E�̑I��������
				for (Window* targetWindow : GetWindows()) {
					targetWindow->ClearSelectedTriggerRect();
				}

				//�E�B���h�E�O���[�v���O�̃E�B���h�E�O���[�v�Ƃ͈Ⴄ�Ȃ�
				if ((typeid(*parentWindow) == typeid(GameWindow)) != canUseGameWnd) {
					//�E�B���h�E���Q�[����ʂȂ�Q�[����ʂ̂ݎg����
					canUseGameWnd = (typeid(*parentWindow) == typeid(GameWindow));
				}
			}
		}
	}

	if (typeid(*activeWindow) == typeid(GameWindow) && canUseGameWnd || !(typeid(*activeWindow) == typeid(GameWindow)) && !canUseGameWnd) {
		//�C�x���g�`�F�b�N
		activeWindow->EventCheck();
	}

	for (Window* parentWindow : GetWindows()) {
		parentWindow->Update();
	}

	//Ctrl + S����������
	if (Input::GetKey(Input::KeyCode::LEFT_CONTROL, false) && Input::GetKeyDown(Input::KeyCode::S, false)) {
		//�V�[�����Z�[�u
		SceneManager::SaveScene();
	}
	//Ctrl + F����������
	if (Input::GetKey(Input::KeyCode::LEFT_CONTROL, false) && Input::GetKeyDown(Input::KeyCode::F, false)) {
		//�X�N���v�g���쐬
		std::vector<std::filesystem::path> scriptPathes;
		//.h
		scriptPathes.push_back(std::filesystem::path(ProjectFileManager::currentPath.string() + "\\Script.h"));
		//.cpp
		scriptPathes.push_back(std::filesystem::path(ProjectFileManager::currentPath.string() + "\\Script.cpp"));
		for (auto& scriptPath : scriptPathes) {
			//�t�@�C�������݂��Ȃ��Ȃ�
			if (!std::filesystem::exists(scriptPath)) {
				//���̃t�@�C���^�C�v���m�F���đ��v�����Ȃ�
				if (ProjectFileManager::IsFileType(scriptPath)) {
					//�t�@�C�����쐬
					std::ofstream ofs(scriptPath);
					//�t�@�C�����`�F�b�N
					ProjectFileManager::CheckAddFile(scriptPath);
					//�c���[���X�g�Ƀt�H���_����ǉ�
					WindowManager::projectWindow->SetFileChildrenToTreeList(scriptPath);
					//�t�H���_���\���X�V
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

WindowManager::WindowManager()
{
	gameWindow = new GameWindow();
	hierarchyWindow = new HierarchyWindow();
	inspectorWindow = new InspectorWindow();
	projectWindow = new ProjectWindow();
	projectWindow->Init();

	activeWindow = gameWindow;	//�����̓Q�[�����
}

GameWindow* WindowManager::gameWindow = nullptr;
HierarchyWindow* WindowManager::hierarchyWindow = nullptr;
InspectorWindow* WindowManager::inspectorWindow = nullptr;
ProjectWindow* WindowManager::projectWindow = nullptr;

Window* WindowManager::activeWindow = nullptr;	//�����̓Q�[�����

bool WindowManager::canUseGameWnd = true;	//�ŏ��͎g����
