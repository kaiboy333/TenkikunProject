#include "SceneIcon.h"
#include "ProjectFileManager.h"

SceneIcon::SceneIcon(float startX, float startY, float iconWidth, float iconHeight, float blankWidth, float blankHeight, std::filesystem::path path) : FileIcon(startX, startY, iconWidth, iconHeight, blankWidth, blankHeight, static_cast<Image*>(ProjectFileManager::pathAndInfo[ProjectFileManager::resourceFilePath.string() + "\\Tenkikun.png"]), path)
{
    //イベントを追加(ダブルクリックをしたら)
    this->mouseDoubleClickEvents.push_back(std::make_pair(GetEventNo(), [this]() {
        //エディットモードなら
        if (SceneManager::playMode == SceneManager::PlayMode::EDIT) {
            //このパスのファイル名にあるシーンを読み込む
            SceneManager::LoadScene(this->GetFileNameNotExtension());
        }
    }));
}
