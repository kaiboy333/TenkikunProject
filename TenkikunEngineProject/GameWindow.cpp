#include "GameWindow.h"
#include "SceneManager.h"

GameWindow::GameWindow() : Window(300, 0, 700, 500)
{

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

    //画像のアルファ値設定
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

    //灰色の四角を描画
    DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(169, 169, 169), TRUE);

    //シーンの描画
    Scene* scene = SceneManager::GetNowScene();
    if (scene != nullptr) {
        scene->Draw(this);
    }
}
