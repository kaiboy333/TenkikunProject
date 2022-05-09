#pragma once

#include <iostream>
#include <vector>

template<class T>
class Condition
{
	public:
		std::string name;
		T value;

		std::vector<std::string> types;
		int index = 0;

		Condition(std::string name);

		virtual bool isMeetCondition(T value) = 0;	//条件を満たしているか
};

template<class T>
inline Condition<T>::Condition(std::string name)
{
	this->name = name;
}
