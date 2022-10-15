#pragma once

#include <unordered_map>
#include <iostream>
#include "Component.h"
#include "Animation.h"
#include "ImageRenderer.h"
#include "Animator.h"
#include "AnimationState.h"
#include "AnimationParamater.h"
#include "Info.h"

class Animation;
class AnimationState;
class Animator;
class AnimatorController : public Info
{
	public:
		void AddIntParamater(std::string name, int value);
		void AddFloatParamater(std::string name, float value);
		void AddBoolParamater(std::string name, bool value);

		std::vector<AnimationParamater*> paramaters;

		std::vector<AnimationState*> states;

		AnimatorController(std::filesystem::path path);

		AnimationParamater* GetParamater(std::string name);	//���O����p�����[�^���擾

		virtual void PreparationLibrate() override;
};

