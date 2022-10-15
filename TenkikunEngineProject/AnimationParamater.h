#pragma once

#include <string>
#include "SceneInfo.h"

class AnimationParamater : public SceneInfo
{
	public:
		enum class Type {
			Int,
			Float,
			Bool,
		};

		Type type = Type::Int;

		std::string name = "";

		int intValue = 0;
		float floatValue = 0;
		bool boolValue = false;

		float GetValue();

		virtual void PreparationLibrate() override;
};

