#pragma once

#include "Window.h"
#include "GameWindow.h"
#include "HierarchyWindow.h"
#include "InspectorWindow.h"

class GameWindow;
class HierarchyWindow;
class InspectorWindow;
class WindowManager
{
	public:
		static GameWindow* gameWindow;
		static HierarchyWindow* hierarchyWindow;
		static InspectorWindow* inspectorWindow;

		static Window* activeWindow;

		static void Update();	//��ʂ̃}�E�X�`�F�b�N
		static void Draw();

		static vector<Window*> GetWindows();	//���݂��邷�ׂẴE�B���h�E���擾

		static bool canUseGameWnd;	//�Q�[����ʂ��������邩
};

