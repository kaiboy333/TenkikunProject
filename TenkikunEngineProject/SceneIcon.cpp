#include "SceneIcon.h"
#include "ProjectFileManager.h"

SceneIcon::SceneIcon(float startX, float startY, float iconWidth, float iconHeight, float blankWidth, float blankHeight, std::filesystem::path path) : FileIcon(startX, startY, iconWidth, iconHeight, blankWidth, blankHeight, static_cast<Image*>(ProjectFileManager::pathAndInfo[ProjectFileManager::resourceFilePath.string() + "\\Tenkikun.png"]), path)
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
