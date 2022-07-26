#pragma once

#include <iostream>
#include <vector>

class AnimationCondition : public SceneInfo
{
	public:
		std::string name;

		float value = 0;

		enum class Mode {
			Equals,
			NotEquals,
			Greater,
			Less,
		};

		Mode mode = Mode::Equals;

		//AnimationCondition(const AnimationCondition& condition);

		bool isMeetCondition(float value);	//ðŒ‚ð–ž‚½‚µ‚Ä‚¢‚é‚©
};

//inline AnimationCondition::AnimationCondition(const AnimationCondition& condition) {
//	//name
//	this->name = condition.name;
//
//	//value
//	this->value = condition.value;
//
//	//mode
//	this->mode = condition.mode;
//}

inline bool AnimationCondition::isMeetCondition(float value)
{
	if (mode == Mode::Greater) {
		return this->value < value;
	}
	else if (mode == Mode::Less) {
		return this->value > value;
	}
	else if (mode == Mode::Equals) {
		return this->value == value;
	}
	else if (mode == Mode::NotEquals) {
		return this->value != value;
	}
	return true;
}
