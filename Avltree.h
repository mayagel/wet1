#pragma once

#ifndef AVLTREE_H
#define AVLTREE_H

#include <algorithm>

template<class C,class D>
class AVLNode {
public:
	D key;
	C data;
	int rank;
	int height;
	AVLNode* left;
	AVLNode* right;
	AVLNode* father;
	AVLNode(const D& key, const C& data, AVLNode* father) :
		key(key), data(data), rank(1), height(0), left(nullptr), right(nullptr), father(father) {};
	~AVLNode() = default;
};

template<class T,class S>
class AVLTree {
private:
	AVLNode<T>* root;

	int getBalanceFactor(AVLNode<T>* node)
	{
		int balance_factor = node == nullptr ? 0 : getHeight(node->left) - getHeight(node->right);
		return balance_factor;
	}

	void balance(AVLNode<T>* node)
	{
		while (node != nullptr)
		{
			if (getBalanceFactor(node) == 2)
			{
				if (getBalanceFactor(node->left) >= 0)
				{
					left_left_rotation(node);
				}
				else if (getBalanceFactor(node->left) == -1)
				{
					left_right_rotation(node);
				}
			}
			else if (getBalanceFactor(node) == -2)
			{
				if (getBalanceFactor(node->right) <= 0)
				{
					right_right_rotation(node);
				}
				else if (getBalanceFactor(node->right) == 1)
				{
					right_left_rotation(node);
				}
			}
			updateRank(node);
			setHeight(node);
			node = node->father;
		}
	}

	void updateRank(AVLNode<T>* node)
	{
		int node_left_rank = node->left == nullptr ? 0 : node->left->rank;
		int node_right_rank = node->right == nullptr ? 0 : node->right->rank;
		node->rank = node_left_rank + node_right_rank + 1;
	}

	void left_left_rotation(AVLNode<T>* node)
	{
		AVLNode<T>* tmp = node->left;
		node->left = tmp->right;
		if (tmp->right != nullptr)
		{
			tmp->right->father = node;
		}
		tmp->father = node->father;
		if (node == root)
		{
			this->root = tmp;
		}
		else
		{
			if (node->father->left == node)
			{
				node->father->left = tmp;
			}
			else
			{
				node->father->right = tmp;
			}
		}
		tmp->right = node;
		node->father = tmp;
		updateRank(node);
		setHeight(node);
		setHeight(tmp);
	}

	void right_right_rotation(AVLNode<T>* node)
	{
		AVLNode<T>* tmp = node->right;
		node->right = tmp->left;
		if (tmp->left != nullptr)
		{
			tmp->left->father = node;
		}
		tmp->father = node->father;
		if (node == root)
		{
			this->root = tmp;
		}
		else
		{
			if (node->father->left == node)
			{
				node->father->left = tmp;
			}
			else
			{
				node->father->right = tmp;
			}
		}
		tmp->left = node;
		node->father = tmp;
		updateRank(node);
		setHeight(node);
		setHeight(tmp);
	}

	void left_right_rotation(AVLNode<T>* node)
	{
		right_right_rotation(node->left);
		left_left_rotation(node);
	}

	void right_left_rotation(AVLNode<T>* node)
	{
		left_left_rotation(node->right);
		right_right_rotation(node);
	}

	void setHeight(AVLNode<T>* node)
	{
		node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
	}

	int getHeight(AVLNode<T>* node)
	{
		int height = node == nullptr ? -1 : node->height;
		return height;
	}

	AVLNode<T>* handleZeroSonsRemove(AVLNode<T>* node)
	{
		if (node->father->left == node)
		{
			node->father->left = nullptr;
		}
		else
		{
			node->father->right = nullptr;
		}
		AVLNode<T>* father = node->father;
		delete node;
		return father;
	}

	AVLNode<T>* handleOneSonRemove(AVLNode<T>* node, LinkedList<T>* swappedNodes)
	{
		if (node->right != nullptr)
		{
			std::swap(node->right->key, node->key);
			std::swap(node->right->data, node->data);
			swappedNodes->insertNode(0, node->right->key);
			swappedNodes->insertNode(0, node->key);
			delete node->right;
			node->right = nullptr;
		}
		else
		{
			std::swap(node->left->key, node->key);
			std::swap(node->left->data, node->data);
			swappedNodes->insertNode(0, node->left->key);
			swappedNodes->insertNode(0, node->key);
			delete node->left;
			node->left = nullptr;
		}
		return node;
	}

	AVLNode<T>* handleTwoSonsRemove(AVLNode<T>* node, LinkedList<T>* swappedNodes)
	{
		AVLNode<T>* tmp = findPrecedingNode(node);

		std::swap(node->key, tmp->key);
		std::swap(node->data, tmp->data);

		swappedNodes->insertNode(0, tmp->key);
		swappedNodes->insertNode(0, node->key);

		bool left_son_exist = tmp->left != nullptr;
		bool right_son_exist = tmp->right != nullptr;

		AVLNode<T>* father;
		if (!left_son_exist && !right_son_exist)
		{
			father = handleZeroSonsRemove(tmp);
		}
		else
		{
			father = handleOneSonRemove(tmp, swappedNodes);
		}
		return father;
	}

	AVLNode<T>* findPrecedingNode(AVLNode<T>* node)
	{
		AVLNode<T>* tmp = node->right;
		while (tmp->left != nullptr)
		{
			tmp = tmp->left;
		}
		return tmp;
	}

	AVLNode<T>* removeFromBST(AVLNode<T>* node, bool left_son_exist, bool right_son_exist,
		LinkedList<T>* swappedNodes)
	{
		AVLNode<T>* father;
		if (!left_son_exist && !right_son_exist)
		{
			father = handleZeroSonsRemove(node);
		}
		else if (left_son_exist && right_son_exist)
		{
			father = handleTwoSonsRemove(node, swappedNodes);
		}
		else
		{
			father = handleOneSonRemove(node, swappedNodes);
		}
		return father;
	}

public:

	AVLTree(AVLNode<T>* root = nullptr) : root(root) {}

	~AVLTree()
	{
		deleteTree(root);
		root = nullptr;
	}

	void deleteTree(AVLNode<T>* node)
	{
		if (node != nullptr)
		{
			deleteTree(node->left);
			deleteTree(node->right);
			delete node;
		}
	}

	AVLNode<T>* getRoot()
	{
		return this->root;
	}

	AVLNode<T>* find(AVLNode<T>* curr_node, const S& key)
	{
		if (curr_node == nullptr || curr_node->key == key)
		{
			return curr_node;
		}
		if (curr_node->key < key)
		{
			return find(curr_node->right, key);
		}
		return find(curr_node->left, key);
	}

	void insert(const S& key, const T& data)
	{
		if (find(root, key) != nullptr)
		{
			throw Failure();
		}
		if (root == nullptr)
		{
			root = new AVLNode<T>(key, data, nullptr);
			setHeight(root);
		}
		else
		{
			AVLNode<T>* tmp = root;
			while (tmp != nullptr)
			{
				if (key < tmp->key)
				{
					if (tmp->left == nullptr)
					{
						tmp->left = new AVLNode<T>(key, data, tmp);
						setHeight(tmp);
						balance(tmp);
						break;
					}
					else
					{
						tmp = tmp->left;
					}
				}
				else
				{
					if (tmp->right == nullptr)
					{
						tmp->right = new AVLNode<T>(key, data, tmp);
						setHeight(tmp);
						balance(tmp);
						break;
					}
					else
					{
						tmp = tmp->right;
					}
				}
			}
		}
	}

	void remove(const T& key, LinkedList<T>* swappedNodes)
	{
		AVLNode<T>* node = find(root, key);
		if (node == nullptr)
		{
			throw Failure();
		}
		bool left_son_exist = node->left != nullptr;
		bool right_son_exist = node->right != nullptr;
		if (node == root)
		{
			if (!left_son_exist && !right_son_exist)
			{
				delete root;
				root = nullptr;
				return;
			}
			else if (right_son_exist && !left_son_exist)
			{
				swappedNodes->insertNode(0, root->right->key);
				swappedNodes->insertNode(0, root->key);
				std::swap(root->key, root->right->key);
				std::swap(root->data, root->right->data);
				delete root->right;
				root->right = nullptr;
				setHeight(root);
				updateRank(root);
				return;
			}
			else if (left_son_exist && !right_son_exist)
			{
				std::swap(root->key, root->left->key);
				std::swap(root->data, root->left->data);
				swappedNodes->insertNode(0, root->left->key);
				swappedNodes->insertNode(0, root->key);
				delete root->left;
				root->left = nullptr;
				setHeight(root);
				updateRank(root);
				return;
			}
		}
		AVLNode<T>* father = removeFromBST(node, left_son_exist, right_son_exist, swappedNodes);
		setHeight(father);
		balance(father);
	}

	AVLNode<T>* select(AVLNode<T>* node, int index)
	{
		int left_degree = node->left == nullptr ? 0 : node->left->rank;
		if (left_degree == index - 1)
		{
			return node;
		}
		else if (left_degree > index - 1)
		{
			return select(node->left, index);
		}
		return select(node->right, index - left_degree - 1);
	}
};
#endif