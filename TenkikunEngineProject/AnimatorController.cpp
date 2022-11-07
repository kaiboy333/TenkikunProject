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

void AnimatorController::AddIntParamater(std::string name, int value = 0)
{
	AnimationParamater* animationParamater = GetParamater(name);
	//新しく作るなら
	if (!animationParamater) {
		animationParamater = new AnimationParamater();
		animationParamater->name = name;
		animationParamater->type = AnimationParamater::Type::Int;

		paramaters.push_back(animationParamater);
	}

	//値をセット
	animationParamater->intValue = value;
}

void AnimatorController::AddFloatParamater(std::string name, float value = 0.0f)
{
	AnimationParamater* animationParamater = GetParamater(name);
	//新しく作るなら
	if (!animationParamater) {
		animationParamater = new AnimationParamater();
		animationParamater->name = name;
		animationParamater->type = AnimationParamater::Type::Float;

		paramaters.push_back(animationParamater);
	}

	//値をセット
	animationParamater->floatValue = value;
}

void AnimatorController::AddBoolParamater(std::string name, bool value = false)
{
	AnimationParamater* animationParamater = GetParamater(name);
	//新しく作るなら
	if (!animationParamater) {
		animationParamater = new AnimationParamater();
		animationParamater->name = name;
		animationParamater->type = AnimationParamater::Type::Bool;

		paramaters.push_back(animationParamater);
	}

	//値をセット
	animationParamater->boolValue = value;
}