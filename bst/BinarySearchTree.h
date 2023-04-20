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
	int Difference(Node<T>*);
	Node<T>* Rr_rotat(Node<T>*);
	Node<T>* Ll_rotat(Node<T>*);
	Node<T>* Lr_rotat(Node<T>*);
	Node<T>* Rl_rotat(Node<T>*);
	Node<T>* Balance(Node<T>*);
	int CountDepth(Node<T>* startNode) const;
	void CopyAllNodes(Node<T>* currentNode);
	Node<T>* SearchNode(T value);
	void Print(const std::shared_ptr<Node<T>>& node) const;
	size_t m_size;
	std::shared_ptr<Node<T>> m_root = nullptr;
};

template<typename T>
inline int BinarySearchTree<T>::Difference(Node<T>*)
{
	int l_height = CountDepth(m_root.get()->left);
	int r_height = CountDepth(m_root.get()->right);
	int b_factor = l_height - r_height;
	return b_factor;
}

template<typename T>
inline Node<T>* BinarySearchTree<T>::Rr_rotat(Node<T>* parent)
{
	Node<T>* t;
	t = parent->right;
	parent->right = t->left;
	t->left = parent;
	return t;
}

template<typename T>
inline Node<T>* BinarySearchTree<T>::Ll_rotat(Node<T>* parent)
{
	Node<T>* t;
	t = parent->left;
	parent->left = t->right;
	t->right = parent;
	return t;
}

template<typename T>
inline Node<T>* BinarySearchTree<T>::Lr_rotat(Node<T>* parent)
{
	Node<T>* t;
	t = parent->left;
	parent->left = rr_rotat(t);
	return ll_rotat(parent);
}

template<typename T>
inline Node<T>* BinarySearchTree<T>::Rl_rotat(Node<T>* parent)
{
	Node<T>* t;
	t = parent->right;
	parent->right = ll_rotat(t);
	return rr_rotat(parent);
}

template<typename T>
inline Node<T>* BinarySearchTree<T>::Balance(Node<T>*)
{
	int bal_factor = difference(m_root.get());
	if (bal_factor > 1)
	{
		if (difference(m_root.get()->left) > 0)
			m_root.get() = ll_rotat(m_root.get());
		else
			m_root.get() = lr_rotat(m_root.get());
	}
	else if (bal_factor < -1)
	{
		if (difference(m_root.get()->right) > 0)
			m_root.get() = rl_rotat(m_root.get());
		else
			m_root.get() = rr_rotat(m_root.get());
	}
	return m_root.get();
}

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
	auto leftDepth = CountDepth(nodeToRemove->left.get() + 1);
	auto rightDepth = CountDepth(nodeToRemove->right.get() + 1);
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
		int left = CountDepth(currentNode->left.get() + 1);
		int right = CountDepth(currentNode->right.get() + 1);
		if (right >= left)
		{
			return depth + right - 1;
		}
		else
		{
			return depth + left - 1;
		}
	}
	return depth - 1;
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
