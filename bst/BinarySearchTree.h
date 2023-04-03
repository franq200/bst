#pragma once
#include <exception>
#include <iostream>

template <typename T>
struct Node
{
	Node<T>& operator= (const Node<T>& right);
	T value;
	Node<T>* left = nullptr;
	Node<T>* right = nullptr;
};

template <typename T>
class BinarySearchTree
{
public:
	void DeleteNodes(Node<T>* currentNode);
	void Insert(T value);
	const T& Search(T value);
	void Remove(T value);
	void PrintAll() const;
	size_t GetSize() const;
private:
	int CountDepth(Node<T>* startNode) const;
	void CopyAllNodes(Node<T>* currentNode);
	Node<T>* SearchNode(T value);
	void Print(std::unique_ptr<Node<T>> node) const;
	size_t m_size;
	std::unique_ptr<Node<T>> m_root = std::make_unique<Node<T>>(nullptr);
};

template<typename T>
inline void BinarySearchTree<T>::DeleteNodes(Node<T>* currentNode)
{
	Node<T>* leftNode = currentNode->left;
	Node<T>* rightNode = currentNode->right;
	delete currentNode;
	if (rightNode != nullptr)
	{
		DeleteNodes(rightNode);
	}
	if (leftNode != nullptr)
	{
		DeleteNodes(leftNode);
	}
}

template<typename T>
inline void BinarySearchTree<T>::Insert(T value)
{
	if (m_root == nullptr)
	{
		m_root = std::make_unique<Node<T>>(value); ///////////////////////////////////////////////////////////////
	}
	else
	{
		std::unique_ptr<Node<T>> currentNode = m_root;
		std::unique_ptr<Node<T>> beforeCurrentNode = std::make_unique<Node<T>>(nullptr);
		std::cout << "Insert before while loop " << currentNode << '\n';
		while (currentNode != std::make_unique<Node<T>>(nullptr))
		{
			beforeCurrentNode = std::make_unique<Node<T>>(currentNode);
			if (value < currentNode->value)
			{
				currentNode = std::make_unique<Node<T>>(currentNode->left);
			}
			else if (value > currentNode->value)
			{
				currentNode = std::make_unique<Node<T>>(currentNode->right);
			}
		}
		std::cout << "Insert after while loop " << currentNode << '\n';

		if (value < beforeCurrentNode->value)
		{
			std::make_unique<Node<T>>(beforeCurrentNode->left) = std::make_unique<Node<T>>(value); ///////////////////////////////////////////////////////////////
		}
		else if (value > beforeCurrentNode->value)
		{
			std::make_unique<Node<T>>(beforeCurrentNode->right) = std::make_unique<Node<T>>(value); ///////////////////////////////////////////////////////////////
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
	if (m_root == nullptr)
	{
		throw std::exception("zbiór jest pusty");
	}
	Node<T>* nodeToRemove = SearchNode(value);
	auto leftDepth = CountDepth(nodeToRemove->left);
	auto rightDepth = CountDepth(nodeToRemove->right);
	Node<T> originalRoot = *nodeToRemove;
	if (rightDepth >= leftDepth)
	{
		*nodeToRemove = *nodeToRemove->right;
		CopyAllNodes(originalRoot.left);
		DeleteNodes(originalRoot.left);
	}
	else
	{
		*nodeToRemove = *nodeToRemove->left;
		CopyAllNodes(originalRoot.right);
		DeleteNodes(originalRoot.right);
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
		int left = CountDepth(currentNode->left);
		int right = CountDepth(currentNode->right);
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
		CopyAllNodes(currentNode->left);
		CopyAllNodes(currentNode->right);
	}
}

template<typename T>
inline Node<T>* BinarySearchTree<T>::SearchNode(T value)
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
			return currentNode;
		}
	}
	throw std::exception("Nie ma takiego elementu");
}

template<typename T>
inline void BinarySearchTree<T>::Print(std::unique_ptr<Node<T>> node) const
{
	if (node != nullptr)
	{
		std::cout << node->value << ", ";
		Print(node->left);
		Print(node->right);
	}
}

template<typename T>
inline Node<T>& Node<T>::operator=(const Node<T>& right)
{
	this->left = right.left;
	this->right = right.right;
	this->value = right.value;
	delete& right;
	return *this;
}
