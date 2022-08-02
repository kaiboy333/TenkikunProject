#include "Animator.h"

Animator::Animator(GameObject* gameobject) : Component(gameobject)
{
	
}

void Animator::Update()
{
	//AnimationController�̍X�V
	if (ac != nullptr) {
		//Animation�̍X�V
		//ImageRenderer�̎擾
		ImageRenderer* ir = gameobject->GetComponent<ImageRenderer>();
		//ImageRenderer������̂ł����
		if (ir != nullptr) {
			Animation* animation = nowState->animation;
			//�v�f������Ȃ�
			if ((int)animation->animationKeys.size() != 0) {
				auto iter = animation->animationKeys.find((int)count);
				//����������
				if (iter != animation->animationKeys.end()) {
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
							return;
						}
						else {
							count = (float)lastCount;	//�Ō�̃J�E���g�ɂ���
						}
					}
				}
				count += 1 * nowState->speed;			//���Ԃ̍X�V
			}
		}

		//Transition�̍X�V
		for (AnimationTransition* transition : nowState->transitions) {
			//�������̏ꏊ�ɍs���̂Ȃ�
			if (transition->canTransition(this)) {
				nowState = transition->toState;	//AnimationController��nowState�����̂���State�ɂ���
				count = 0;	//�J�E���^���Z�b�g
				break;	//�I���(���̂͌��Ȃ�)
			}
		}
	}
}

AnimationState* Animator::AddState(Animation* animation, std::string stateName)
{
	AnimationState* state = new AnimationState();	//State���쐬
	//state->ac = animator->GetAnimatorController();	//State��AnimationController���Z�b�g
	state->name = stateName;	//name�Z�b�g
	state->animation = animation;	//State��Animation���Z�b�g
	ac->states.emplace_back(state);	//State�����X�g�ɒǉ�
	//�ŏ��̏ꏊ��null�Ȃ�
	if (nowState == nullptr) {
		nowState = state;	//�ǉ�
		//ImageRenderer���擾
		ImageRenderer* imageRenderer = gameobject->GetComponent<ImageRenderer>();
		//animationKey�̍ŏ��̉摜��Image�ɐݒ�
		imageRenderer->image = animation->animationKeys.begin()->second;
	}
	return state;	//�Ԃ�
}
