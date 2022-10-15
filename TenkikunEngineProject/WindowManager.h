#pragma once

#include "Window.h"
#include "GameWindow.h"
#include "HierarchyWindow.h"
#include "InspectorWindow.h"
#include "ProjectWindow.h"
#include "MenuList.h"
#include "PlayWindow.h"

class GameWindow;
class HierarchyWindow;
class InspectorWindow;
class ProjectWindow;
class WindowManager : Rect
{
	public:
		static GameWindow* gameWindow;
		static HierarchyWindow* hierarchyWindow;
		static InspectorWindow* inspectorWindow;
		static ProjectWindow* projectWindow;
		static PlayWindow* playWindow;

		//static Window* activeWindow;

		static const float WIDTH;
		static const float HEIGHT;

		WindowManager();

		static void Update();	//��ʂ̃}�E�X�`�F�b�N
		static void Draw();

		static vector<Window*> GetWindows();	//���݂��邷�ׂẴE�B���h�E���擾

		static void SetSelectedTriggerRect(TriggerRect* selectedTriggerRect);	//�w���TriggerRect��I�����ꂽ��Ԃɂ���(�O�͉̂���)
		static void ClearSelectedTriggerRect();	//���ׂĂ̑I�����ꂽ��Ԃ�TriggerRect����������

		static TriggerRect* GetSelectedTriggerRect();

		static bool canUseGameWnd;	//�Q�[����ʂ𑀍쒆��

		static std::vector<std::pair<int, std::function<void()>>> activeEvents;	//���s�ł���C�x���g�֐�

		static void RemoveTriggerRect(TriggerRect* triggerRect);
		static void AddTriggerRect(TriggerRect* triggerRect);

		static void EventCheck();	//�C�x���g�g���K�[�`�F�b�N

		static void SetMenuList(MenuList* menuList);
		static MenuList* GetMenuList();

	private:
		static std::vector<TriggerRect*> triggerRects;	//��������l�p����

		static TriggerRect* selectedTriggerRect;	//�I�𒆂�TriggerRect

		static MenuList* menuList;	//���ꂽ���j���[���X�g
};

