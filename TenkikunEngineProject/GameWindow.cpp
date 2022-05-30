#include "GameWindow.h"
#include "SceneManager.h"

GameWindow::GameWindow() : Window(700, 500, 300, 0)
{

}

void GameWindow::Draw()
{
    //�o�b�N�̕`��
    Window::Draw();

    //�D�F�̎l�p��`��
    DrawBoxAA(startX, startY, startX + width - 1, startY + height - 1, GetColor(169, 169, 169), TRUE);

    //�V�[���̕`��
    Scene* scene = SceneManager::GetNowScene();
    if (scene != nullptr) {
        scene->Draw(this);
    }
}
