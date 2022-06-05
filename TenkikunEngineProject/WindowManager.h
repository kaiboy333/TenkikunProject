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

		static std::vector<TriggerRect*> triggerRects;	//��������l�p����

		static void Update();	//��ʂ̃}�E�X�`�F�b�N
		static void Draw();

		static void SetSelectedTriggerRect(TriggerRect* selectedTriggerRect);
		static TriggerRect* GetSelectedTriggerRect();

	private:
		static TriggerRect* selectedTriggerRect;	//�I�𒆂�TriggerRect
};

