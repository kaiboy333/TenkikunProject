#include "AnimatorController.h"

void AnimatorController::Update()
{
	//State�̍X�V
	if (nowState != nullptr) {
		nowState->Update();
	}
}

AnimationState* AnimatorController::AddAnimation(Animation* animation)
{
	AnimationState* state = new AnimationState(this);	//State���쐬
	state->animation = animation;	//State��Animation���Z�b�g
	this->states.emplace_back(state);	//State�����X�g�ɒǉ�
	//�ŏ��̏ꏊ��null�Ȃ�
	if (nowState == nullptr) {
		nowState = state;	//�ǉ�
	}
	return state;	//�Ԃ�
}

void AnimatorController::AddIntParamater(std::string name, int value = 0)
{
	AnimationParamater* animationParamater = new AnimationParamater(name);
	animationParamater->type = AnimationParamater::Type::Int;
	animationParamater->intValue = value;

	paramaters.insert_or_assign(name, animationParamater);
}

void AnimatorController::AddFloatParamater(std::string name, float value = 0.0f)
{
	AnimationParamater* animationParamater = new AnimationParamater(name);
	animationParamater->type = AnimationParamater::Type::Float;
	animationParamater->floatValue = value;

	paramaters.insert_or_assign(name, animationParamater);
}

void AnimatorController::AddBoolParamater(std::string name, bool value = false)
{
	AnimationParamater* animationParamater = new AnimationParamater(name);
	animationParamater->type = AnimationParamater::Type::Bool;
	animationParamater->boolValue = value;

	paramaters.insert_or_assign(name, animationParamater);
}