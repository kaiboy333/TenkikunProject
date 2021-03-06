#include "Animator.h"

void Animator::Update()
{
	//AnimationControllerの更新
	if (ac != nullptr) {
		ac->Update();
	}
}

void Animator::SetAnimationController(AnimatorController* ac)
{
	this->ac = ac;
	ac->animator = this;	//acにAnimatorを紐づける
}

AnimatorController* Animator::GetAnimatorController()
{
	return ac;
}
