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
				auto iter = animation->animationKeys.begin();
				for (int i = 0; i < index; i++) {
					iter++;
				}
				//�J�E���g���w��̃J�E���g��蒴���Ă���Ȃ�
				if ((*iter).first <= (int)count) {
					//�Ō�̗v�f�Ȃ�
					if ((int)animation->animationKeys.size() - 1 == index) {
						//�J��Ԃ��A�j���[�V�����𓮂����Ȃ�
						if (animation->isLoop) {
							count = 0;	//�J�E���^���Z�b�g
							index = 0;
						}
						else {
							count = (float)((*iter).first);	//�Ō�̃J�E���g�ɂ���
						}
						return;
					}
					Image* image = iter->second;
					int gh = image->GetGH();
					ir->image = image;	//�V�����摜���Z�b�g
					index++;	//���̗v�f��
				}
				////����������
				//else {
				//	iter--;	//�Ō�̗v�f������
				//	//�����A�����Ă���̂��Ō�̏ꏊ��������(�Ō�̃t���[�����߂��Ă�����)
				//	int lastCount;
				//	if ((lastCount = iter->first) <= (int)count) {
				//	}
				//}
				count += nowState->speed;			//���Ԃ̍X�V
			}
		}

		//Transition�̍X�V
		for (AnimationTransition* transition : nowState->transitions) {
			//�������̏ꏊ�ɍs���̂Ȃ�
			if (transition->canTransition(this)) {
				nowState = transition->toState;	//AnimationController��nowState�����̂���State�ɂ���
				count = 0;	//�J�E���^���Z�b�g
				index = 0;
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

void Animator::PreparationLibrate()
{
	ac = nullptr;
	nowState = nullptr;

	//���g�̉������
	Component::PreparationLibrate();
}
