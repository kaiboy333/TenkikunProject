#include "MonoBehaviour.h"
#include "SceneManager.h"

void MonoBehaviour::Update()
{
	//�v���C���Ă��鎞����
	if (SceneManager::playMode == SceneManager::PlayMode::PLAY) {
		if (isFirstUpdate) {
			MonoStart();	//�ŏ������Ă΂��
			isFirstUpdate = false;	//2��ڂ���͌Ă΂�Ȃ�
		}
		MonoUpdate();
	}
}
