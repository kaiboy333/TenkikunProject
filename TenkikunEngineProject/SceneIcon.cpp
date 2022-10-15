#include "SceneIcon.h"
#include "ProjectFileManager.h"

SceneIcon::SceneIcon(float startX, float startY, float iconWidth, float iconHeight, float blankWidth, float blankHeight, std::string imageFileName, std::filesystem::path path) : FileIcon(startX, startY, iconWidth, iconHeight, blankWidth, blankHeight, imageFileName, path)
{
    //�C�x���g��ǉ�(�_�u���N���b�N��������)
    this->mouseDoubleClickEvents.push_back(std::make_pair(GetEventNo(), [this]() {
        //�G�f�B�b�g���[�h�Ȃ�
        if (SceneManager::playMode == SceneManager::PlayMode::EDIT) {
            //���̃p�X�̃t�@�C�����ɂ���V�[����ǂݍ���
            SceneManager::LoadScene(this->GetFileNameNotExtension());
        }
    }));
}
