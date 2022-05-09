#include "Animator.h"

void Animator::Update()
{
	//AnimationController‚ÌXV
	if (ac != nullptr) {
		ac->Update();
	}
}

void Animator::SetAnimationController(AnimatorController* ac)
{
	this->ac = ac;
	ac->animator = this;	//ac‚ÉAnimator‚ð•R‚Ã‚¯‚é
}

AnimatorController* Animator::GetAnimatorController()
{
	return ac;
}
