#include "AnimatorController.h"

AnimatorController::AnimatorController(std::filesystem::path path) : Info(path)
{

}

AnimationParamater* AnimatorController::GetParamater(std::string name)
{
	for (AnimationParamater* paramater : paramaters) {
		if (paramater->name == name) {
			return paramater;
		}
	}

	return nullptr;
}

void AnimatorController::PreparationLibrate()
{
	paramaters.clear();

	states.clear();
}

//
//AnimatorController::AnimatorController(const AnimatorController& ac)
//{
//	//���O���R�s�[
//	this->name = ac.name;
//
//	//nowState���R�s�[
//	this->nowState = new AnimationState(*ac.nowState);
//
//	//states���R�s�[
//	for (AnimationState* state : ac.states) {
//		this->states.push_back(new AnimationState(*state));
//	}
//}

//void AnimatorController::Update(Animator* animator)
//{
//	//State�̍X�V
//	if (nowState != nullptr) {
//		nowState->Update(animator);
//	}
//}

//AnimationState* AnimatorController::AddState(Animation* animation, std::string stateName)
//{
//	AnimationState* state = new AnimationState();	//State���쐬
//	//state->ac = animator->GetAnimatorController();	//State��AnimationController���Z�b�g
//	state->name = stateName;	//name�Z�b�g
//	state->animation = animation;	//State��Animation���Z�b�g
//	states.emplace_back(state);	//State�����X�g�ɒǉ�
//	//�ŏ��̏ꏊ��null�Ȃ�
//	if (nowState == nullptr) {
//		nowState = state;	//�ǉ�
//	}
//	return state;	//�Ԃ�
//}

void AnimatorController::AddIntParamater(std::string name, int value = 0)
{
	AnimationParamater* animationParamater = new AnimationParamater();
	animationParamater->name = name;
	animationParamater->type = AnimationParamater::Type::Int;
	animationParamater->intValue = value;

	paramaters.push_back(animationParamater);
}

void AnimatorController::AddFloatParamater(std::string name, float value = 0.0f)
{
	AnimationParamater* animationParamater = new AnimationParamater();
	animationParamater->name = name;
	animationParamater->type = AnimationParamater::Type::Float;
	animationParamater->floatValue = value;

	paramaters.push_back(animationParamater);
}

void AnimatorController::AddBoolParamater(std::string name, bool value = false)
{
	AnimationParamater* animationParamater = new AnimationParamater();
	animationParamater->name = name;
	animationParamater->type = AnimationParamater::Type::Bool;
	animationParamater->boolValue = value;

	paramaters.push_back(animationParamater);
}