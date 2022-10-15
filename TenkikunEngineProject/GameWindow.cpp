#include "GameWindow.h"
#include "SceneManager.h"

GameWindow::GameWindow() : Window(300, 50, 700, 450)
{
    frameText = new TextRect(startX, startY, "");
}

void GameWindow::Update()
{
    Window::Update();

    //ƒV[ƒ“‚ÌXV
    Scene* scene = SceneManager::GetNowScene();
    if (scene != nullptr) {
        scene->Update();
    }
}

void GameWindow::Draw()
{
    //ƒoƒbƒN‚Ì•`‰æ
    Window::Draw();

    //ŠDF‚ÌŽlŠp‚ð•`‰æ
    DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(169, 169, 169), TRUE);

    //ƒV[ƒ“‚Ì•`‰æ
    Scene* scene = SceneManager::GetNowScene();
    if (scene != nullptr) {
        scene->Draw();
    }

    //frameText‚Ì•`‰æ
    frameText->Draw();
}
