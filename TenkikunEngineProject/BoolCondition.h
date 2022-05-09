#pragma once
#include "Condition.h"

class BoolCondition : public Condition<bool>
{
	public:
		BoolCondition(std::string name);

		bool isMeetCondition(bool value) override;
};

inline BoolCondition::BoolCondition(std::string name) : Condition<bool>(name)
{
	value = true;

	types.emplace_back("true");
	types.emplace_back("false");
}

inline bool BoolCondition::isMeetCondition(bool value)
{
	std::string type = "None";
	if (index >= 0 && index < types.size()) {
		type = types[index];
	}

	bool b = true;
	if (type == "false") {
		b = false;
	}

	return !(this->value ^ value);
}
