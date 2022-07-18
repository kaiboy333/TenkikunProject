#pragma once

#include <iostream>
#include <vector>

class AnimationCondition
{
public:
	std::string name;

	float value;

	enum class Mode {
		Equals,
		NotEquals,
		Greater,
		Less,
	};

	Mode mode;

	AnimationCondition(std::string name, float value = 0, Mode mode = Mode::Equals);

	bool isMeetCondition(float value);	//ðŒ‚ð–ž‚½‚µ‚Ä‚¢‚é‚©
};

inline AnimationCondition::AnimationCondition(std::string name, float value, Mode mode)
{
	this->name = name;
	this->value = value;
	this->mode = mode;
}

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
