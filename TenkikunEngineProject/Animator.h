#pragma once

#include "AnimatorController.h"
#include <iostream>
#include <unordered_map>

class AnimatorController;
class Animator : public Component
{
	public:
		void Update() override;

		void SetAnimationController(AnimatorController* ac);	//�A�j���[�V�����R���g���[���[��ǉ����A�A�j���[�^�[�Ɏ��g�̃|�C���^��R�Â���

		AnimatorController* GetAnimatorController();	//�A�j���[�V�����R���g���[���[���擾

	private:
		AnimatorController* ac = nullptr;
};

