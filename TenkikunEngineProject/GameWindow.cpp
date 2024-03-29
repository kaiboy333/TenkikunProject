#include "GameWindow.h"
#include "SceneManager.h"

GameWindow::GameWindow() : Window(300, 50, 700, 450)
{
    frameText = new TextRect(startX, startY, "");
}

void GameWindow::Update()
{
    Window::Update();

    //シーンの更新
    Scene* scene = SceneManager::GetNowScene();
    if (scene != nullptr) {
        scene->Update();
    }
}

void GameWindow::Draw()
{
    //バックの描画
    Window::Draw();

    //灰色の四角を描画
    DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(169, 169, 169), TRUE);

    //シーンの描画
    Scene* scene = SceneManager::GetNowScene();
    if (scene != nullptr) {
        scene->Draw();
    }

    //frameTextの描画
    frameText->Draw();
}
