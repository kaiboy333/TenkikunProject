#pragma once

#include "Window.h"
#include "TreeList.h"
#include "ProjectFileManager.h"

class TreeList;
class ProjectWindow : public Window
{
	public:
		TreeList* treeList = nullptr;

		ProjectFileManager* projectFileManager = nullptr;

		ProjectWindow();

		void Init();

		virtual void Update() override;

		virtual void Draw() override;
};

