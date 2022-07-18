#include "AnimationParamater.h"

AnimationParamater::AnimationParamater(std::string name)
{
	this->name = name;
}

float AnimationParamater::GetValue()
{
	if (type == Type::Int) {
		return (float)intValue;
	}
	else if (type == Type::Float) {
		return floatValue;
	}
	else if (type == Type::Bool) {
		return (float)boolValue;
	}
}
