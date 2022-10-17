#pragma once

template <class T>
class BinaryNode
{
	public:
		T key;
		BinaryNode<T>* left = nullptr;
		BinaryNode<T>* right = nullptr;

		BinaryNode(T key);
};

template<class T>
inline BinaryNode<T>::BinaryNode(T key)
{
	this->key = key;
}
