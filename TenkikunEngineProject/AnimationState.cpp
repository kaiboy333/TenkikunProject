#include "AnimationState.h"
#include <algorithm>

AnimationTransition* AnimationState::AddTransition(AnimationState* toState)
{
	AnimationTransition* transition = new AnimationTransition();	//Transition�쐬
	//transition->ac = ac;
	transition->fromState = this;
	transition->toState = toState;
	transitions.emplace_back(transition);	//���X�g�ɒǉ�
	return transition;
}

void AnimationState::PreparationLibrate()
{
	animation = nullptr;

	transitions.clear();
}

//AnimationState::AnimationState()
//{
//}
//
//AnimationState::AnimationState(const AnimationState& state)
//{
//	//name
//	this->name = state.name;
//
//	//animation
//	this->animation = new Animation(*state.animation);
//
//	//speed
//	this->speed = state.speed;
//
//	//count
//	this->count = state.count;
//}

void AnimationState::Update(Animator* animator)
{
	////Animation�̍X�V
	////ImageRenderer�̎擾
	//ImageRenderer* ir = animator->gameobject->GetComponent<ImageRenderer>();
	////ImageRenderer������̂ł����
	//if (ir != nullptr) {
	//	auto iter = animation->animationKeys.find((int)count);
	//	//����������
	//	if (iter != animation->animationKeys.end()) {
	//		Image* image = iter->second;
	//		int gh = image->GetGH();
	//		ir->image = image;	//�V�����摜���Z�b�g
	//	}
	//	//����������
	//	else {
	//		iter--;	//�Ō�̗v�f������
	//		//�����A�����Ă���̂��Ō�̏ꏊ��������(�Ō�̃t���[�����߂��Ă�����)
	//		int lastCount;
	//		if ((lastCount = iter->first) <= (int)count) {
	//			//�J��Ԃ��A�j���[�V�����𓮂����Ȃ�
	//			if (animation->isLoop) {
	//				count = 0;	//�J�E���^���Z�b�g
	//			}
	//			else {
	//				count = (float)lastCount;	//�Ō�̃J�E���g�ɂ���
	//			}
	//		}
	//	}
	//	count += 1 * speed;			//���Ԃ̍X�V
	//}

	////Transition�̍X�V
	//for (AnimationTransition* transition : transitions) {
	//	//�������̏ꏊ�ɍs���̂Ȃ�
	//	if (transition->canTransition(animator)) {
	//		animator->ac->nowState = transition->toState;	//AnimationController��nowState�����̂���State�ɂ���
	//		count = 0;	//�J�E���^���Z�b�g
	//		break;	//�I���(���̂͌��Ȃ�)
	//	}
	//}
}
