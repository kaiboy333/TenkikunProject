#include "GameWindow.h"
#include "SceneManager.h"

GameWindow::GameWindow() : Window(300, 0, 700, 500)
{
    frameText = new TextRect(startX, startY, "");

    //ƒ}ƒEƒX‚ð‰Ÿ‚µ‚½uŠÔ
    mouseClickDownEvents.push_back(std::make_pair(GetEventNo(), [this]() {
        //ƒQ[ƒ€‰æ–Ê‚ªŽg‚¦‚é‚æ‚¤‚É
        WindowManager::canUseGameWnd = true;
    }));
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
