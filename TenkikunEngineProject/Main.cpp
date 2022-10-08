#include "DxLib.h"
#include <iostream>
#include "GameWindow.h"
#include <vector>
#include "SceneManager.h"
#include <tchar.h>
#include <mmsystem.h>
#include <string>
#include "PlayerScript.h"
#include "Input.h"
#include "Rotate.h"
#include "ImageManager.h"
#include "resource.h"
#include "ProjectFileManager.h"
#include "FontManager.h"
#include "Debug.h"
#include "Time.h"

#pragma comment(lib,"winmm.lib")

// �{���̓O���[�o���ɂ��Ȃ������ǂ�

void Init();
void Update();
void Draw();

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	SetMainWindowText("Tenkikun Engine");
	ChangeWindowMode(TRUE); //�E�B���h�E���[�h�ŋN��
	SetGraphMode((int)WindowManager::WIDTH, (int)WindowManager::HEIGHT, 32); //��ʂ̉𑜓x�w��
	SetWindowSizeChangeEnableFlag(FALSE); //��ʃT�C�Y�ύX�s��
	SetDrawScreen(DX_SCREEN_BACK);	//����ʂŕ`��
	SetWindowIconID(IDI_TENKIKUN);	//�E�B���h�E�A�C�R���ݒ�
	DragFileInfoClear();	//�h���b�v�t�@�C�����̏�����
	SetAlwaysRunFlag(true);		//�o�b�N�O���E���h�ł�������p��
	SetDragFileValidFlag(true);		//�h���b�O�A���h�h���b�v������


	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}


	Init();	//������

	//���C�����[�v
	while (ProcessMessage() == 0) {
		Update();	//�X�V

		Draw();	//�`��

		ScreenFlip();	//��ʗ��Ԃ�
	}


	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}

inline void Init() {
	Time();	//�^�C���}�l�[�W���[�̏�����
	ProjectFileManager();	//�t�@�C���}�l�[�W���[�̏�����
	ImageManager();	//�C���[�W�}�l�[�W���[�̏�����
	FontManager();	//�t�H���g�}�l�[�W���[�̏�����
	WindowManager();	//�Q�[����ʂ̏�����
	SceneManager();	//�V�[���}�l�[�W���[�̏�����
	Input();	//���͂̏�����
}

inline void Update() {
	Time::Update();	//���Ԃ̍X�V
	ProjectFileManager::Update(); //ProjectFileManager�̍X�V
	WindowManager::Update();	//Window�̍X�V
	Input::Update();	//�L�[�̍X�V
}

inline void Draw() {
	WindowManager::Draw();	//�E�B���h�E��ʂ�`��
}