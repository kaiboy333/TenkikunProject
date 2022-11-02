#include "FileIcon.h"
#include "ImageManager.h"
#include "FontManager.h"
#include "ProjectFileManager.h"
#include "SceneIcon.h"

FileIcon::FileIcon(float startX, float startY, float iconWidth, float iconHeight, float blankWidth, float blankHeight, std::string imageFileName, std::filesystem::path path) : TriggerRect(startX, startY, 2 * blankWidth + iconWidth, 2 * blankHeight + iconHeight + FontManager::systemFont->GetFontHeight(), 1)
{
	iconGH = ImageManager::LoadAndGetImage(imageFileName);	//�摜���擾
	this->iconWidth = iconWidth;
	this->iconHeight = iconHeight;
	this->blankWidth = blankWidth;
	this->blankHeight = blankHeight;
	this->path = path;	//�΂ɂȂ�t�@�C���̃p�X���Z�b�g
	fileNameRect = new TextBox(startX + blankWidth - overWidth / 2, startY + blankHeight + iconHeight, iconWidth + overWidth, FontManager::systemFont->GetFontHeight(), false, path.filename().string());	//TextBox�쐬
	//�G���^�[�L�[��������
	fileNameRect->pushEnterEvents.push_back(std::make_pair(fileNameRect->GetEventNo(), [this]() {
		//�ς����Ȃ��悤�ɂȂ�
		this->fileNameRect->canChange = false;
		//�V�������O���擾
		std::string newName = this->fileNameRect->GetText();
		//�O�Ɠ������O�Ȃ�I���
		if (newName == this->path.filename().string())
			return;
		//TreeFile�̖��O��ύX
		TreeNode* node = WindowManager::projectWindow->treeList->FindNode(this->path.string().substr(ProjectFileManager::assetParentPathName.length()));
		node->SetElement(newName);
		//�t�@�C���̖��O��ύX
		std::string newFileParentPath = this->path.string().substr(0, this->path.string().length() - this->path.filename().string().length());
		std::filesystem::rename(this->path, newFileParentPath + newName);
		//�_�t�@�C���̖��O��ύX
		std::filesystem::rename(this->path.string() + ".kumo", newFileParentPath + newName + ".kumo");
		//�p�X��ς���
		this->path = newFileParentPath + newName;
		//loadfile();
	}));

	this->mouseClickDownEvents.push_back(std::make_pair(GetEventNo(), [this]() {
		//�N���b�N�����Ƃ��Ɏ��g��I�𒆂ɂ���
		WindowManager::SetSelectedTriggerRect(this);
	}));

	//�E�N���b�N����������
	mouseRightClickEvents.push_back(std::make_pair(GetEventNo(), [this](void) {
		//�I��Ώۂɂ���
		WindowManager::SetSelectedTriggerRect(this);

		Vector3 mousePos = Input::GetMousePosition();

		MenuList* menuList0 = new MenuList(mousePos.x, mousePos.y, { "Rename", "Delete", "B", "C" });
		MenuNode* menuNode0_0 = menuList0->FindNode("Rename");
		menuNode0_0->mouseClickDownEvents.insert(menuNode0_0->mouseClickDownEvents.begin(), std::make_pair(menuNode0_0->GetEventNo(), [this]() {
			//�ύX�\�ɂ���
			fileNameRect->canChange = true;
			//�N���b�N�����̂Ɠ���������s��
			fileNameRect->mouseClickDownEvents[0].second();
		}));
		MenuNode* menuNode0_1 = menuList0->FindNode("Delete");
		menuNode0_1->mouseClickDownEvents.insert(menuNode0_1->mouseClickDownEvents.begin(), std::make_pair(menuNode0_1->GetEventNo(), [this]() {
			//�t�@�C�������݂���Ȃ�
			if (std::filesystem::exists(this->path)) {
				//�t�@�C��(�t�H���_)���폜
				std::filesystem::remove_all(this->path);
				//TreeList������폜
				WindowManager::projectWindow->treeList->Delete(this->path.string().substr(ProjectFileManager::assetParentPathName.length()));

				//�_�t�@�C��������Ȃ�
				if (std::filesystem::exists(this->path.string() + ".kumo")) {
					//�_�t�@�C���폜
					std::filesystem::remove(this->path.string() + ".kumo");
					//TreeList������폜
					WindowManager::projectWindow->treeList->Delete(std::string(this->path.string() + ".kumo").substr(ProjectFileManager::assetParentPathName.length()));
				}

				//filePrint�̕\���X�V
				WindowManager::projectWindow->filePrintRect->LoadFoler();

				//�t�@�C���A�C�R�����V�[���A�C�R����������
				if (typeid(this) == typeid(SceneIcon*)) {
					//�V�[���p�X���X�g����폜
					SceneManager::scenePathes.erase(this->GetFileNameNotExtension());
				}
			}
		}));
		//WindowManager�ɃZ�b�g
		WindowManager::SetMenuList(menuList0);
	}));
}

void FileIcon::Draw()
{
	if (iconGH) {
		int imageWidth, imageHeight;
		GetGraphSize(iconGH, &imageWidth, &imageHeight);

		if (!GetIsSelected() && GetIsTopOn()) {
			//�D�F��`��
			DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(200, 200, 200), TRUE);
		}

		if (isImageIcon) {
			//�A�C�R�����̎l�p��`��(�A�C�R���w�i)
			DrawBoxAA(startX + blankWidth, startY + blankHeight, startX + blankWidth + iconWidth, startY + blankHeight + iconHeight, GetColor(100, 100, 100), TRUE);
		}

		//�t�@�C�����̕`��
		fileNameRect->Draw();

		//�摜�̕`��
		DrawRotaGraph3F(startX + blankWidth + iconWidth / 2, startY + blankHeight + iconHeight / 2, imageWidth / 2.0f, imageHeight / 2.0f, iconWidth / imageWidth, iconHeight / imageHeight, 0, iconGH, TRUE);

		//�I������Ă�����
		if (GetIsSelected()) {
			//�摜�̃A���t�@�l�ݒ�
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
			//�F��`��
			DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(30, 144, 255), TRUE);
			//�摜�̃A���t�@�l��߂�
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		}
	}
}

const float FileIcon::overWidth = 15;

void FileIcon::PreparationLibrate()
{
	//TextBox�̏����A���
	fileNameRect->PreparationLibrate();
	delete(fileNameRect);
	fileNameRect = nullptr;

	//���g�̏���
	TriggerRect::PreparationLibrate();
}

std::string FileIcon::GetFileNameNotExtension()
{
	std::string fileName = path.filename().string();

	return fileName.substr(0, fileName.length() - path.filename().extension().string().length());
}
