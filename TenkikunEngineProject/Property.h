#pragma once

#include <iostream>
#include <functional>

template<class T>
class Property
{
	public:
		T& r;
		std::function<void(T v)> set = nullptr;
		std::function<T()> get = nullptr;

		operator T() {
			return get ? this->get() : this->r;
		}

		T operator ->() {
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

		void operator +=(const T v) {
			if (set) {
				this->set(r += v);
			}
			else {
				r += v;
			}
		}

		void operator -=(const T v) {
			if (set) {
				this->set(r -= v);
			}
			else {
				r -= v;
			}
		}

		void operator *=(const T v) {
			if (set) {
				this->set(r *= v);
			}
			else {
				r *= v;
			}
		}

		void operator /=(const T v) {
			if (set) {
				this->set(r /= v);
			}
			else {
				r /= v;
			}
		}
};

