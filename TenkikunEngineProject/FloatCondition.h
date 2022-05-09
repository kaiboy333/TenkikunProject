#pragma once
#include "Condition.h"

class FloatCondition : public Condition<float>
{
	public:
		FloatCondition(std::string name);

		bool isMeetCondition(float value) override;
};

inline FloatCondition::FloatCondition(std::string name) : Condition<float>(name)
{
	value = 0.0f;

	types.emplace_back("Greater");
	types.emplace_back("Less");
}

inline bool FloatCondition::isMeetCondition(float value)
{
	std::string type = "None";
	if (index >= 0 && index < types.size()) {
		type = types[index];
	}

	if (type == "Greater") {
		return this->value < value;
	}
	else if (type == "Less") {
		return this->value > value;
	}
	return true;
}