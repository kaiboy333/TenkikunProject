#pragma once

#include <string>

class AnimationParamater : public SceneInfo
{
	public:
		enum class Type {
			Int,
			Float,
			Bool,
		};

		Type type = Type::Int;

		std::string name;

		int intValue;
		float floatValue;
		bool boolValue;

		AnimationParamater(std::string name);

		float GetValue();
};

