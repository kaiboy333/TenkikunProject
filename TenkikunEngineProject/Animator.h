#pragma once

#include "AnimatorController.h"
#include <iostream>
#include <unordered_map>

class AnimatorController;
class Animator : public Component
{
	public:
		void Update() override;

		void SetAnimationController(AnimatorController* ac);	//アニメーションコントローラーを追加し、アニメーターに自身のポインタを紐づける

		AnimatorController* GetAnimatorController();	//アニメーションコントローラーを取得

	private:
		AnimatorController* ac = nullptr;
};

