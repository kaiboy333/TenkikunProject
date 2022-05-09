#include "GameWindow.h"
#include "SceneManager.h"

GameWindow::GameWindow(int width, int height) : Window(width, height, 0, 0)
{

}

void GameWindow::Draw()
{
    Scene* scene = SceneManager::GetNowScene();
    if (scene != nullptr) {
        if(scene->cameras.size() != 0){
            scene->cameras[this->drawCameraNo]->Draw(this);   //Œ»İ‚Ì‘ÎÛ‚ÌCamera‚ğ•`‰æ
        }
    }
}
