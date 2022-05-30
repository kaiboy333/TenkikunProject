#include "GameWindow.h"
#include "SceneManager.h"

GameWindow::GameWindow() : Window(700, 500, 300, 0)
{

}

void GameWindow::Draw()
{
    //バックの描画
    Window::Draw();

    //灰色の四角を描画
    DrawBoxAA(startX, startY, startX + width - 1, startY + height - 1, GetColor(169, 169, 169), TRUE);

    //シーンの描画
    Scene* scene = SceneManager::GetNowScene();
    if (scene != nullptr) {
        scene->Draw(this);
    }
}
