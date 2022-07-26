#pragma once

#include <unordered_map>
#include <iostream>
#include "Component.h"
#include "Animation.h"
#include "ImageRenderer.h"
#include "Animator.h"
#include "AnimationState.h"
#include "AnimationParamater.h"

class Animation;
class AnimationState;
class Animator;
class AnimatorController : public Info
{
	public:
		//Animator* animator = nullptr;
		//AnimationState* nowState = nullptr;

		//AnimatorController();
		//AnimatorController(const AnimatorController& ac);	//コピーコンストラクタ

		//void Update(Animator* animator);

		void AddIntParamater(std::string name, int value);
		void AddFloatParamater(std::string name, float value);
		void AddBoolParamater(std::string name, bool value);

		std::unordered_map<std::string, AnimationParamater*> paramaters;

		std::vector<AnimationState*> states;
};

