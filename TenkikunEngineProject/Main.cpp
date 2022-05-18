#include "DxLib.h"
#include <iostream>
#include "GameWindow.h"
#include <vector>
#include "SceneManager.h"
#include <Windows.h>
#include <tchar.h>
#include <mmsystem.h>
#include <string>
#include "Script.h"
#include "PlayerScript.h"
#include "Input.h"
#include "Rotate.h"
#include "WindowManager.h"

#pragma comment(lib,"winmm.lib")

#define WIDTH 600
#define HEIGHT 500

// �{���̓O���[�o���ɂ��Ȃ������ǂ�
const float MIN_FRAME_TIME = 1.0f / 60;
LARGE_INTEGER timeStart;
LARGE_INTEGER timeEnd;
LARGE_INTEGER timeFreq;

void Init();
void CulculateFPS();
void Update();
void Draw();

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
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

	// ���C�����[�v�ɓ���O�ɐ��x���擾���Ă���
	if (QueryPerformanceFrequency(&timeFreq) == FALSE) { // ���̊֐���0(FALSE)���A�鎞�͖��Ή�
		// ��������QueryPerformanceFrequency���g���Ȃ��l��(�Â�)PC�ł͂ǂ����F�X�L�c�C���낤��
		return(E_FAIL); // �{���͂���ȋA������Ă͍s���Ȃ�(�㑱�̉���������Ă΂�Ȃ�)
	}
	// 1�x�擾���Ă���(����v�Z�p)
	QueryPerformanceCounter(&timeStart);

	Init();	//������

	//���C�����[�v
	while (ProcessMessage() == 0) {
		CulculateFPS();	//FPS�̌v�Z

		Update();	//�X�V

		Draw();	//�`��

		ScreenFlip();	//��ʗ��Ԃ�

	}


	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}

inline void Init() {
	SceneManager();	//�V�[���}�l�[�W���[�̏�����
	WindowManager();	//�Q�[����ʂ̏�����
	Input();	//���͂̏�����

	Scene* scene = SceneManager::GetNowScene();	//�V�[�����擾

	GameObject* player = scene->CreateEmpty();	//�v���C���[�I�u�W�F�N�g���쐬
	player->transform->position = Vector3(0, 0, 0);
	player->name = "Player";
	PlayerScript* script = player->AddComponent<PlayerScript>();	//�v���C���[�X�N���v�g�쐬

	GameObject* square = GameObject::Find("Square");
	square->transform->SetParent(player->transform);
	square->transform->position = Vector3(50, 0, 0);
	square->AddComponent<Rotate>();

	GameObject* square2 = GameObject::Find("Square2");
	square2->transform->SetParent(square->transform);
	square2->transform->position = Vector3(150, 0, 0);
	square2->transform->scale = Vector3(0.5f, 0.5f, 1);
}

inline void CulculateFPS() {
	// ���̎��Ԃ��擾
	QueryPerformanceCounter(&timeEnd);
	// (���̎��� - �O�t���[���̎���) / ���g�� = �o�ߎ���(�b�P��)
	double frameTime = static_cast<double>(timeEnd.QuadPart - timeStart.QuadPart) / static_cast<double>(timeFreq.QuadPart);

	if (frameTime < MIN_FRAME_TIME) { // ���Ԃɗ]�T������
		// �~���b�ɕϊ�
		DWORD sleepTime = static_cast<DWORD>((MIN_FRAME_TIME - frameTime) * 1000);

		timeBeginPeriod(1); // ����\���グ��(�������Ȃ���Sleep�̐��x�̓K�^�K�^)
		Sleep(sleepTime);   // �Q��
		timeEndPeriod(1);   // �߂�
	}

	double fps = 1 / frameTime;

	//OutputDebugString("FPS:");	//FPS��\��
	//OutputDebugString(std::to_string(fps).c_str());	//FPS��\��
	//OutputDebugString("\n");	//FPS��\��

	timeStart = timeEnd; // ����ւ�
}

inline void Update() {
	Scene* scene = SceneManager::GetNowScene();
	scene->Update();	//���݂̃V�[���̍X�V
	Input::Update();	//�L�[�̍X�V
}

inline void Draw() {
	//��ʑS�̂����ŕ`��
	DrawBoxAA(0, 0, WIDTH, HEIGHT, GetColor(0, 0, 0), TRUE);

	WindowManager::Draw();	//�E�B���h�E��ʂ�`��
}