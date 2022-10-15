#include "AnimationParamater.h"

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

	return 0;
}

void AnimationParamater::PreparationLibrate()
{

}
