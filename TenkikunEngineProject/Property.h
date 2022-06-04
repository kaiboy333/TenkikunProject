#pragma once

#include <iostream>
#include <functional>

template<class T>
class Property
{
	public:
		Property(T& r, std::function<void(T v)> set = nullptr, std::function<T()> get = nullptr);

		operator T() {
			return get ? this->get() : this->r;
		}

		T* operator ->() {
			return get ? this->get() : this->r;
		}

		void operator =(const T v) {
			if (set) {
				this->set(v);
			}
			else {
				r = v;
			}
		}


	private:
		T& r;
		std::function<void(T v)> set = nullptr;
		std::function<T()> get = nullptr;
};

template<class T>
inline Property<T>::Property(T& r, std::function<void(T v)> set, std::function<T()> get)
{
	this->r = r;
	this->set = set;
	this->get = get;
}
