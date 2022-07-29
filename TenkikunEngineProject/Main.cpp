#include "DxLib.h"
#include <iostream>
#include "GameWindow.h"
#include <vector>
#include "SceneManager.h"
#include <Windows.h>
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

#pragma comment(lib,"winmm.lib")

constexpr auto WIDTH = 1300;
constexpr auto HEIGHT = 800;

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
	SetMainWindowText("Tenkikun Engine");
	ChangeWindowMode(TRUE); //�E�B���h�E���[�h�ŋN��
	SetGraphMode(WIDTH, HEIGHT, 32); //��ʂ̉𑜓x�w��
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
	ProjectFileManager();	//�t�@�C���}�l�[�W���[�̏�����
	ImageManager();	//�C���[�W�}�l�[�W���[�̏�����
	FontManager();	//�t�H���g�}�l�[�W���[�̏�����
	WindowManager();	//�Q�[����ʂ̏�����
	SceneManager();	//�V�[���}�l�[�W���[�̏�����
	Input();	//���͂̏�����

	//Scene* scene = SceneManager::GetNowScene();	//�V�[�����擾

	//GameObject* player = scene->CreateEmpty();	//�v���C���[�I�u�W�F�N�g���쐬
	//player->transform->position = Vector3(0, 0, 0);
	//player->SetName("Player");
	//PlayerScript* script = player->AddComponent<PlayerScript>();	//�v���C���[�X�N���v�g�쐬

	//GameObject* square = scene->CreateSquare();
	//square->transform->SetParent(player->transform);
	//square->transform->position = Vector3(50, 0, 0);
	////square->AddComponent<Rotate>();

	//GameObject* square2 = scene->CreateSquare();
	//square2->transform->SetParent(square->transform);
	//square2->transform->position = Vector3(150, 0, 0);
	//square2->transform->scale = Vector3(0.5f, 0.5f, 1);

	//GameObject* square3 = scene->CreateSquare();
	//square3->transform->position = Vector3(-100, 0, 0);
	//square3->transform->scale = Vector3(1, 1, 1);

	//scene->CreateEmpty();
	//scene->CreateEmpty();
	//scene->CreateEmpty();

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

	//Debug::Log("FPS : " + std::to_string(fps));	//FPS��\��
	//Debug::Log("time : " + std::to_string(frameTime));	//FPS��\��

	timeStart = timeEnd; // ����ւ�
}

inline void Update() {
	ProjectFileManager::Update(); //ProjectFileManager�̍X�V
	WindowManager::Update();	//Window�̍X�V
	Input::Update();	//�L�[�̍X�V
}

inline void Draw() {
	//�摜�̃A���t�@�l�ݒ�
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

	//��ʑS�̂����ŕ`��
	DrawBoxAA(0, 0, WIDTH, HEIGHT, GetColor(0, 0, 0), TRUE);

	WindowManager::Draw();	//�E�B���h�E��ʂ�`��
}