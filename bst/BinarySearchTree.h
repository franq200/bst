#pragma once
#include <exception>

template <typename T>
struct Node
{
	T value;
	Node<T>* left = nullptr;
	Node<T>* right = nullptr;
};

template <typename T>
class BinarySearchTree
{
public:
	void Insert(T value);
	const T& Search(T value);
	void Remove(T value);
	size_t GetSize() const;
private:
	size_t m_size;
	Node<T>* m_root = nullptr;
};

template<typename T>
inline void BinarySearchTree<T>::Insert(T value)
{
	if (m_root == nullptr)
	{
		m_root = new Node<T>{value};
	}
	else
	{
		Node<T>* currentNode = m_root;
		Node<T>* beforeCurrentNode = nullptr;
		while (currentNode != nullptr)
		{
			beforeCurrentNode = currentNode;
			if (value < currentNode->value)
			{
				currentNode = currentNode->left;
			}
			else if (value > currentNode->value)
			{
				currentNode = currentNode->right;
			}
		}

		if (value < beforeCurrentNode->value)
		{
			beforeCurrentNode->left = new Node<T>{ value };
		}
		else if (value > beforeCurrentNode->value)
		{
			beforeCurrentNode->right = new Node<T>{ value };
		}
	}
}

template<typename T>
inline const T& BinarySearchTree<T>::Search(T value)
{
	if (m_root == nullptr)
	{
		throw std::exception("zbiór jest pusty");
	}

	Node<T>* currentNode = m_root;
	while (currentNode != nullptr)
	{
		if (value < currentNode->value)
		{
			currentNode = currentNode->left;
		}
		else if (value > currentNode->value)
		{
			currentNode = currentNode->right;
		}
		if (currentNode->value == value)
		{
			return currentNode->value;
		}
	}
	throw std::exception("Nie ma takiego elementu");
}

template<typename T>
inline void BinarySearchTree<T>::Remove(T value)
{
}

template<typename T>
inline size_t BinarySearchTree<T>::GetSize() const
{
	return m_size;
}
