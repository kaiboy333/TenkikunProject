#include "Script.h"
#include "SceneManager.h"

//void Script::SetMonoBehaviour(MonoBehaviour* mono)
//{
//	this->mono = mono;
//	//MonoBehaviour�ɃQ�[���I�u�W�F�N�g��Transform���Z�b�g
//	this->mono->gameobject = gameobject;
//	this->mono->transform = gameobject->transform;
//}
//
//MonoBehaviour* Script::GetMonoBehaviour()
//{
//	return mono;
//}
//
//void Script::Update()
//{
//	if (mono) {
//		//�v���C���Ă��鎞����
//		if (SceneManager::playMode == SceneManager::PlayMode::PLAY) {
//			if (isFirstUpdate) {
//				mono->Start();	//�ŏ������Ă΂��
//				isFirstUpdate = false;	//2��ڂ���͌Ă΂�Ȃ�
//			}
//			mono->Update();
//		}
//	}
//}
