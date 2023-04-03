#pragma once
#include <exception>
#include <iostream>
#include <memory>

template <typename T>
struct Node
{
	Node(const T&);
	Node(Node<T>&);
	Node<T>& operator=(Node<T>& right);

	T value;
	std::shared_ptr<Node<T>> left = nullptr;
	std::shared_ptr<Node<T>> right = nullptr;
};

template <typename T>
class BinarySearchTree
{
public:
	void Insert(T value);
	const T& Search(T value);
	void Remove(T value);
	void PrintAll() const;
	size_t GetSize() const;
private:
	int CountDepth(Node<T>* startNode) const;
	void CopyAllNodes(Node<T>* currentNode);
	Node<T>* SearchNode(T value);
	void Print(const std::shared_ptr<Node<T>>& node) const;
	size_t m_size;
	std::shared_ptr<Node<T>> m_root = nullptr;
};

template<typename T>
inline void BinarySearchTree<T>::Insert(T value)
{
	if (m_root == nullptr)
	{
		m_root = std::make_shared<Node<T>>(value); ///////////////////////////////////////////////////////////////
	}
	else
	{
		Node<T>* currentNode = m_root.get();
		Node<T>* beforeCurrentNode = nullptr;
		std::cout << "Insert before while loop " << currentNode << '\n';
		while (currentNode != nullptr)
		{
			beforeCurrentNode = currentNode;
			if (value < currentNode->value)
			{
				currentNode = currentNode->left.get();
			}
			else if (value > currentNode->value)
			{
				currentNode = currentNode->right.get();
			}
		}
		std::cout << "Insert after while loop " << currentNode << '\n';

		if (value < beforeCurrentNode->value)
		{
			beforeCurrentNode->left = std::make_shared<Node<T>>(value); ///////////////////////////////////////////////////////////////
		}
		else if (value > beforeCurrentNode->value)
		{
			beforeCurrentNode->right = std::make_shared<Node<T>>(value); ///////////////////////////////////////////////////////////////
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

	Node<T>* currentNode = m_root.get();
	while (currentNode != nullptr)
	{
		if (value < currentNode->value)
		{
			currentNode = currentNode->left.get();
		}
		else if (value > currentNode->value)
		{
			currentNode = currentNode->right.get();
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
	if (m_root == nullptr)
	{
		throw std::exception("zbiór jest pusty");
	}
	Node<T>* nodeToRemove = SearchNode(value);
	auto leftDepth = CountDepth(nodeToRemove->left.get());
	auto rightDepth = CountDepth(nodeToRemove->right.get());
	Node<T> originalRoot = *nodeToRemove;
	if (rightDepth >= leftDepth)
	{
		*nodeToRemove = *nodeToRemove->right;
		CopyAllNodes(originalRoot.left.get());
	}
	else
	{
		*nodeToRemove = *nodeToRemove->left;
		CopyAllNodes(originalRoot.right.get());
	}
}

template<typename T>
inline void BinarySearchTree<T>::PrintAll() const
{
	Print(m_root);
}

template<typename T>
inline size_t BinarySearchTree<T>::GetSize() const
{
	return m_size;
}

template<typename T>
inline int BinarySearchTree<T>::CountDepth(Node<T>* startNode) const
{
	Node<T>* currentNode = startNode;
	int depth = 0;
	if (currentNode != nullptr)
	{
		depth++;
		int left = CountDepth(currentNode->left.get());
		int right = CountDepth(currentNode->right.get());
		if (right >= left)
		{
			return depth + right;
		}
		else
		{
			return depth + left;
		}
	}
	return depth;
}

template<typename T>
inline void BinarySearchTree<T>::CopyAllNodes(Node<T>* currentNode)
{
	if (currentNode != nullptr)
	{
		Insert(currentNode->value);
		CopyAllNodes(currentNode->left.get());
		CopyAllNodes(currentNode->right.get());
	}
}

template<typename T>
inline Node<T>* BinarySearchTree<T>::SearchNode(T value)
{
	if (m_root == nullptr)
	{
		throw std::exception("zbiór jest pusty");
	}

	Node<T>* currentNode = m_root.get();
	while (currentNode != nullptr)
	{
		if (value < currentNode->value)
		{
			currentNode = currentNode->left.get();
		}
		else if (value > currentNode->value)
		{
			currentNode = currentNode->right.get();
		}
		if (currentNode->value == value)
		{
			return currentNode;
		}
	}
	throw std::exception("Nie ma takiego elementu");
}

template<typename T>
inline void BinarySearchTree<T>::Print(const std::shared_ptr<Node<T>>& node) const
{
	if (node != nullptr)
	{
		std::cout << node->value << ", ";
		Print(node->left);
		Print(node->right);
	}
}

template<typename T>
inline Node<T>& Node<T>::operator=(Node<T>& right)
{
	this->left = right.left;
	this->right = right.right;
	this->value = right.value;
	return *this;
}

template<typename T>
inline Node<T>::Node(Node<T>& node)
{
	this->left = node.left;
	this->right = node.right;
	this->value = node.value;
}

template<typename T>
inline Node<T>::Node(const T& value)
{
	this->value = value;
}
