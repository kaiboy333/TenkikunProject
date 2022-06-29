#pragma once

#include "Window.h"
#include "TreeList.h"
#include "FilePrintRect.h"

class TreeList;
class FilePrintRect;
class ProjectWindow : public Window
{
	public:
		TreeList* treeList = nullptr;

		FilePrintRect* filePrintRect = nullptr;

		ProjectWindow();

		void Init();

		virtual void Update() override;

		virtual void Draw() override;

		void SetFileChildrenToTreeList(std::filesystem::path addPath);	//�w��̃p�X�ȉ������ׂăc���[���X�g�ɒǉ�
};

