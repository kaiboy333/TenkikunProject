#include "GameWindow.h"
#include "SceneManager.h"

GameWindow::GameWindow(int width, int height) : Window(width, height, 0, 0)
{

}

void GameWindow::Draw()
{
    Scene* scene = SceneManager::GetNowScene();
    if (scene != nullptr) {
        scene->Draw(this);
    }
}
