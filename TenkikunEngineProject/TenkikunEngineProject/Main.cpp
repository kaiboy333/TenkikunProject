#include "DxLib.h"

#define WIDTH 600
#define HEIGHT 500

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetMainWindowText("Practice");
	ChangeWindowMode(TRUE); //�E�B���h�E���[�h�ŋN��
	SetGraphMode(WIDTH, HEIGHT, 32); //��ʂ̉𑜓x�w��
	SetWindowSizeChangeEnableFlag(FALSE); //��ʃT�C�Y�ύX�s��
	SetDrawScreen(DX_SCREEN_BACK);	//����ʂŕ`��

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	//���C�����[�v
	while (ProcessMessage() == 0) {
		//��ʑS�̂����ŕ`��
		DrawBoxAA(0, 0, WIDTH, HEIGHT, GetColor(0, 0, 0), TRUE);

		//�l�p�`��`��
		DrawBoxAA(WIDTH / 2.0 - WIDTH / 4.0, HEIGHT / 2.0 - HEIGHT / 4.0, WIDTH / 2.0 + WIDTH / 4.0, HEIGHT / 2.0 + HEIGHT / 4.0, GetColor(255, 255, 255), TRUE);


		DrawPixel(320, 240, GetColor(255, 255, 255));	// �_��ł�

		ScreenFlip();	//��ʗ��Ԃ�

	}


	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}