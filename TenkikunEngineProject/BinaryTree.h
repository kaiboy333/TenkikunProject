#pragma once

#include <vector>
#include "BinaryNode.h"

template <class T>
class BinaryTree
{
	public:
		BinaryTree<T>(BinaryNode<T>* root);

		BinaryNode<T>* Find(T key);

		BinaryNode<T>* GetRoot();

	private:
		BinaryNode<T>* root = nullptr;
};

template<class T>
inline BinaryNode<T>* BinaryTree<T>::Find(T key)
{
	std::vector<BinaryNode<T>*> nodes = { root };

	while ((int)nodes.size() != 0) {
		BinaryNode<T>* node = nodes[0];
		nodes.erase(0);

		if (key == node) {
			return node;
		}

		if (node->left) {
			nodes.push_back(node->left);
		}
		if (node->right) {
			nodes.push_back(node->right);
		}
	}

	return nullptr;
}

template<class T>
inline BinaryNode<T>* BinaryTree<T>::GetRoot()
{
	return root;
}

template<class T>
inline BinaryTree<T>::BinaryTree(BinaryNode<T>* root)
{
	this->root = root;
}
