#include "Animator.h"

void Animator::Update()
{
	//AnimationController�̍X�V
	if (ac != nullptr) {
		ac->Update();
	}
}

void Animator::SetAnimationController(AnimatorController* ac)
{
	this->ac = ac;
	ac->animator = this;	//ac��Animator��R�Â���
}

AnimatorController* Animator::GetAnimatorController()
{
	return ac;
}
