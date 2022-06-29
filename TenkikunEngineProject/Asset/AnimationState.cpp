#include "AnimationState.h"
#include "IntCondition.h"
#include <algorithm>

AnimationTransition* AnimationState::AddTransition(AnimationState* toState)
{
	AnimationTransition* transition = new AnimationTransition(this, toState, ac);	//Transition�쐬
	transitions.emplace_back(transition);	//���X�g�ɒǉ�
	return transition;
}

AnimationState::AnimationState(AnimatorController* ac)
{
	this->ac = ac;
}

void AnimationState::Update()
{
	//Animation�̍X�V
	//�A�j���[�V�����R���g���[���[�ɃA�j���[�^�[���R�Â��Ă����
	if (ac->animator != nullptr) {
		ImageRenderer* ir = ac->animator->gameobject->GetComponent<ImageRenderer>();	//ImageRenderer�擾
		//ImageRenderer������̂ł����
		if (ir != nullptr) {
			auto iter = animation->frameAndImages.find((int)count);
			//����������
			if (iter != animation->frameAndImages.end()) {
				Image* image = iter->second;
				int gh = image->GetGH();
				ir->image = image;	//�V�����摜���Z�b�g
			}
			//����������
			else {
				iter--;	//�Ō�̗v�f������
				//�����A�����Ă���̂��Ō�̏ꏊ��������(�Ō�̃t���[�����߂��Ă�����)
				int lastCount;
				if ((lastCount = iter->first) <= (int)count) {
					//�J��Ԃ��A�j���[�V�����𓮂����Ȃ�
					if (animation->isLoop) {
						count = 0;	//�J�E���^���Z�b�g
					}
					else {
						count = (float)lastCount;	//�Ō�̃J�E���g�ɂ���
					}
				}
			}
			count += 1 * speed;			//���Ԃ̍X�V
		}
	}

	//Transition�̍X�V
	for (AnimationTransition* transition : transitions) {
		//�������̏ꏊ�ɍs���̂Ȃ�
		if (transition->canTransition()) {
			ac->nowState = transition->toState;	//AnimationController��nowState�����̂���State�ɂ���
			count = 0;	//�J�E���^���Z�b�g
			break;	//�I���(���̂͌��Ȃ�)
		}
	}
}
