#pragma once
#include "Condition.h"

class IntCondition : public Condition<int>
{
	public:
		IntCondition(std::string name);

		bool isMeetCondition(int value) override;
};


inline IntCondition::IntCondition(std::string name) : Condition<int>(name)
{
	value = 0;

	types.emplace_back("Greater");
	types.emplace_back("Less");
	types.emplace_back("Equals");
	types.emplace_back("NotEqual");
}

inline bool IntCondition::isMeetCondition(int value)
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
	else if (type == "Equals") {
		return this->value == value;
	}
	else if (type == "NotEqual") {
		return this->value != value;
	}
	return true;
}
