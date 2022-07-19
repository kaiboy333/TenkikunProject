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
class AnimatorController : public SceneInfo
{
	public:
		Animator* animator = nullptr;
		AnimationState* nowState = nullptr;

		void Update();

		AnimationState* AddAnimation(Animation* animation);

		void AddIntParamater(std::string name, int value);
		void AddFloatParamater(std::string name, float value);
		void AddBoolParamater(std::string name, bool value);

		std::unordered_map<std::string, AnimationParamater*> paramaters;

		std::filesystem::path path;	//コントローラーのパス

		void SetName(std::string name);
		std::string GetName();

		std::vector<AnimationState*> GetStates();

	private:
		std::vector<AnimationState*> states;

		std::string name;

};

