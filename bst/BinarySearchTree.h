#pragma once
#include <exception>
#include <iostream>

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
	~BinarySearchTree();
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
	void Print(Node<T>* node) const;
	size_t m_size;
	Node<T>* m_root = nullptr;
};

template<typename T>
inline BinarySearchTree<T>::~BinarySearchTree()
{
	DeleteNodes(m_root);
}

template<typename T>
inline void BinarySearchTree<T>::DeleteNodes(Node<T>* currentNode)
{
	Node<T>* nodeToDelete = currentNode;
	if (currentNode->right != nullptr)
	{
		currentNode = currentNode->right;
		delete nodeToDelete;
		DeleteNodes(currentNode);
	}
	if (currentNode->left != nullptr)
	{
		currentNode = currentNode->left;
		delete nodeToDelete;
		DeleteNodes(currentNode);
	}
}

template<typename T>
inline void BinarySearchTree<T>::Insert(T value)
{
	if (m_root == nullptr)
	{
		m_root = new Node<T>{ value };
	}
	else
	{
		Node<T>* currentNode = m_root;
		Node<T>* beforeCurrentNode = nullptr;
		std::cout << "Insert before while loop " << currentNode << '\n';
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
		std::cout << "Insert after while loop " << currentNode << '\n';

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
	if (m_root == nullptr)
	{
		throw std::exception("zbiór jest pusty");
	}
	Node<T>* nodeToRemove = SearchNode(value); // 0x1234
	auto leftDepth = CountDepth(nodeToRemove->left);
	auto rightDepth = CountDepth(nodeToRemove->right);
	Node<T> originalRoot = *nodeToRemove; // 0x1234
	if (rightDepth >= leftDepth)
	{
		*nodeToRemove = *nodeToRemove->right; // 0x1235
		CopyAllNodes(originalRoot.left);
	}
	else
	{
		*nodeToRemove = *nodeToRemove->left; //
		CopyAllNodes(originalRoot.right);
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
inline void BinarySearchTree<T>::Print(Node<T>* node) const
{
	if (node != nullptr)
	{
		std::cout << node->value << ", ";
		Print(node->left);
		Print(node->right);
	}
}
