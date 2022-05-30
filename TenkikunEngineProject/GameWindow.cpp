#include "GameWindow.h"
#include "SceneManager.h"

GameWindow::GameWindow() : Window(700, 500, 300, 0)
{

}

void GameWindow::Draw()
{
    //ƒoƒbƒN‚Ì•`‰æ
    Window::Draw();

    //ŠDF‚ÌŽlŠp‚ð•`‰æ
    DrawBoxAA(startX, startY, startX + width - 1, startY + height - 1, GetColor(169, 169, 169), TRUE);

    //ƒV[ƒ“‚Ì•`‰æ
    Scene* scene = SceneManager::GetNowScene();
    if (scene != nullptr) {
        scene->Draw(this);
    }
}
