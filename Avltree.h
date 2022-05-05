#pragma once

#ifndef AVLTREE_H
#define AVLTREE_H

#include <algorithm>
#include "Exceptions.h"
#include <iostream>

template <class C, class D>
class AVLNode
{
public:
	D key;
	C data;
	int height;
	AVLNode *left;
	AVLNode *right;
	AVLNode *father;
	AVLNode(){}; // Yagel added empty default constructor
	AVLNode(const D &key, const C &data, AVLNode *father) : key(key), data(data), height(0), left(nullptr), right(nullptr), father(father){};
	AVLNode(AVLNode *node)
	{
		key = node->key;
		data = node->data;
		if (!node->left)
		{
			left = nullptr;
		}
		else
		{
			left = new AVLNode(node->left);
		}
		if (!node->right)
		{
			right = nullptr;
		}
		else
		{
			left = new AVLNode(node->right);
		}
		if (!node->father)
		{
			father = nullptr;
		}
		else
		{
			father = new AVLNode(node->father);
		}
	}
	~AVLNode()
	{
		// if(data)
		// {
		// 	delete data;
		// 	data = nullptr;
		// }
	}
	bool operator<(const AVLNode &node) const
	{
		return this->key < node.key;
	}
	bool operator>(const AVLNode &node) const
	{
		return this->key > node.key;
	}
	AVLNode<C, D> *getRight() { return right; }
	AVLNode<C, D> *getLeft() { return left; }
};

template <class T, class S>
class AVLTree
{
private:
	AVLNode<T, S> *root;
	int num_of_nodes; // added by yagel 06.06

	int getBalanceFactor(AVLNode<T, S> *node)
	{
		int balance_factor = node == nullptr ? 0 : getHeight(node->left) - getHeight(node->right);
		return balance_factor;
	}

	void balance(AVLNode<T, S> *node)
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
			setHeight(node);
			node = node->father;
		}
	}

	void left_left_rotation(AVLNode<T, S> *node)
	{
		AVLNode<T, S> *tmp = node->left;
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
		setHeight(node);
		setHeight(tmp);
	}

	void right_right_rotation(AVLNode<T, S> *node)
	{
		AVLNode<T, S> *tmp = node->right;
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
		setHeight(node);
		setHeight(tmp);
	}

	void left_right_rotation(AVLNode<T, S> *node)
	{
		right_right_rotation(node->left);
		left_left_rotation(node);
	}

	void right_left_rotation(AVLNode<T, S> *node)
	{
		left_left_rotation(node->right);
		right_right_rotation(node);
	}

	void setHeight(AVLNode<T, S> *node)
	{
		node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
	}

	int getHeight(AVLNode<T, S> *node)
	{
		int height = node == nullptr ? -1 : node->height;
		return height;
	}

	AVLNode<T, S> *handleZeroSonsRemove(AVLNode<T, S> *node)
	{
		if (!node->father)
		{
			delete node;
			return nullptr;
		}
		if (node->father->left == node)
		{
			node->father->left = nullptr;
		}
		else
		{
			node->father->right = nullptr;
		}
		AVLNode<T, S> *father = node->father;
		delete node;
		return father;
	}

	AVLNode<T, S> *handleOneSonRemove(AVLNode<T, S> *node)
	{
		if (node->right != nullptr)
		{
			std::swap(node->right->key, node->key);
			std::swap(node->right->data, node->data);
			delete node->right;
			node->right = nullptr;
		}
		else
		{
			std::swap(node->left->key, node->key);
			std::swap(node->left->data, node->data);
			delete node->left;
			node->left = nullptr;
		}
		return node;
	}

	AVLNode<T, S> *handleTwoSonsRemove(AVLNode<T, S> *node)
	{
		AVLNode<T, S> *tmp = findPrecedingNode(node);

		std::swap(node->key, tmp->key);
		std::swap(node->data, tmp->data);

		bool left_son_exist = tmp->left != nullptr;
		bool right_son_exist = tmp->right != nullptr;

		AVLNode<T, S> *father;
		if (!left_son_exist && !right_son_exist)
		{
			father = handleZeroSonsRemove(tmp);
		}
		else
		{
			father = handleOneSonRemove(tmp);
		}
		return father;
	}

	AVLNode<T, S> *findPrecedingNode(AVLNode<T, S> *node)
	{
		AVLNode<T, S> *tmp = node->right;
		while (tmp->left != nullptr)
		{
			tmp = tmp->left;
		}
		return tmp;
	}

	AVLNode<T, S> *removeFromBST(AVLNode<T, S> *node, bool left_son_exist, bool right_son_exist)
	{
		AVLNode<T, S> *father;
		if (!left_son_exist && !right_son_exist)
		{
			father = handleZeroSonsRemove(node);
		}
		else if (left_son_exist && right_son_exist)
		{
			father = handleTwoSonsRemove(node);
		}
		else
		{
			father = handleOneSonRemove(node);
		}
		return father;
	}

public:
	AVLTree(AVLNode<T, S> *root = nullptr) : root(root), num_of_nodes(0) {}

	~AVLTree()
	{
		printf(" avl tree d'tor ");
		deleteTree(root);
		root = nullptr;
	}

	AVLTree operator=(const AVLTree &a)
	{
		this->num_of_nodes = a.num_of_nodes;
		AVLNode<T, S> *new_root = new AVLNode<T, S>(a.root);
		this->root = new_root;
		return *this;
	}

	void printNode(AVLNode<T, S> *node)
	{
		if (!node)
		{
			return;
		}

		std::cout << "info for data : \n";
		std::cout << "carId: " << node->data.typeId << "\n";
		std::cout << "car sells: " << node->data.sells;
		std::cout << ". is it recognize as sell tree?: " << node->data.sells_tree;
	}

	// for testing
	void printTree(AVLNode<T, S> *root)
	{
		if (!root)
		{
			return;
		}

		printTree(root->left);
		printNode(root);
		printTree(root->right);
	}

	void deleteTree(AVLNode<T, S> *node)
	{
		if (node != nullptr)
		{
			deleteTree(node->left);
			deleteTree(node->right);
			delete node;
			node = nullptr;
		}
	}

	AVLNode<T, S> *getRoot()
	{
		return this->root;
	}

	AVLNode<T, S> *find(AVLNode<T, S> *curr_node, const S &key)
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

	void insert(const S &key, const T &data)
	{
		if (root == nullptr)
		{
			root = new AVLNode<T, S>(key, data, nullptr);
			setHeight(root);
		}
		else
		{
			AVLNode<T, S> *tmp = root;
			while (tmp != nullptr)
			{
				if (key < tmp->key)
				{
					if (tmp->left == nullptr)
					{
						tmp->left = new AVLNode<T, S>(key, data, tmp);
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
						tmp->right = new AVLNode<T, S>(key, data, tmp);
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
		num_of_nodes += 1; // added by yagel 06.06
	}

	void remove(const S &key)
	{
		AVLNode<T, S> *node = find(root, key);
		bool left_son_exist = node->left != nullptr;
		bool right_son_exist = node->right != nullptr;
		if (node == root)
		{
			if (!left_son_exist && !right_son_exist)
			{
				delete root;
				root = nullptr;
				num_of_nodes -= 1; // added by yagel 06.06
				return;
			}
			else if (right_son_exist && !left_son_exist)
			{
				std::swap(root->key, root->right->key);
				std::swap(root->data, root->right->data);
				delete root->right;
				root->right = nullptr;
				setHeight(root);
				num_of_nodes -= 1; // added by yagel 06.06
				return;
			}
			else if (left_son_exist && !right_son_exist)
			{
				std::swap(root->key, root->left->key);
				std::swap(root->data, root->left->data);
				delete root->left;
				root->left = nullptr;
				setHeight(root);
				num_of_nodes -= 1; // added by yagel 06.06
				return;
			}
		}
		AVLNode<T, S> *father = removeFromBST(node, left_son_exist, right_son_exist);
		if (father)
		{
			setHeight(father);
			balance(father);
		}
		num_of_nodes -= 1; // added by yagel 06.06
	}

	int getNumOfNode() { return num_of_nodes; } // added by yagel 06.06

	void setNumOfNode(int newNumOfNodes) { num_of_nodes = newNumOfNodes; }

	AVLNode<T, S> **merge(AVLNode<T, S> *arr1[], AVLNode<T, S> *arr2[], int m, int n)
	{
		// mergedArr[] is going to contain result
		AVLNode<T, S> **mergedArr = new AVLNode<T, S> *[m + n];
		int i = 0, j = 0, k = 0;

		// Traverse through both arrays
		while (i < m && j < n)
		{
			// Pick the smaller element and put it in mergedArr
			if (*arr1[i] < *arr2[j])
			{
				mergedArr[k] = arr1[i];
				i++;
			}
			else
			{
				mergedArr[k] = arr2[j];
				j++;
			}
			k++;
		}

		// If there are more elements in first array
		while (i < m)
		{
			mergedArr[k] = arr1[i];
			i++;
			k++;
		}

		// If there are more elements in second array
		while (j < n)
		{
			mergedArr[k] = arr2[j];
			j++;
			k++;
		}

		return mergedArr;
	}

	AVLNode<T, S> *mergeTrees(AVLNode<T, S> *root1, AVLNode<T, S> *root2, int length1, int length2)
	{
		// Store inorder traversal of
		// first tree in an array arr1[]
		AVLNode<T, S> **arr1 = new AVLNode<T, S> *[length1];
		int i = 0;
		storeInorder(new AVLNode<T, S>(root1), arr1, &i);

		// Store inorder traversal of second
		// tree in another array arr2[]
		AVLNode<T, S> **arr2 = new AVLNode<T, S> *[length2];
		int j = 0;
		storeInorder(new AVLNode<T, S>(root2), arr2, &j);

		// Merge the two sorted array into one
		AVLNode<T, S> **mergedArr = merge(arr1, arr2, length1, length2);

		delete[] arr1;
		delete[] arr2;
		// Construct a tree from the merged
		// array and return root of the tree
		AVLNode<T, S> *node = sortedArrayToBST(mergedArr, 0, length1 + length2 - 1, nullptr);
		delete[] mergedArr;
		return node;
	}

	// A helper function that stores inorder
	// traversal of a tree rooted with node
	void storeInorder(AVLNode<T, S> *node, AVLNode<T, S> *inorder[], int *index_ptr)
	{
		if (node == nullptr)
			return;

		/* first recur on left child */
		if (node->left)
		{
			storeInorder(new AVLNode<T, S>(node->left), inorder, index_ptr);
		}
		else
		{
			storeInorder(nullptr, inorder, index_ptr);
		}

		// inorder[*index_ptr] = new AVLNode<T, S> (node->key, node->data, node->father);
		inorder[*index_ptr] = node; // almog change 04.05 0:50
		(*index_ptr)++;				// increase index for next entry
		/* now recur on right child */
		if (node->right)
		{
			storeInorder(new AVLNode<T, S>(node->right), inorder, index_ptr);
		}
		else
		{
			storeInorder(nullptr, inorder, index_ptr);
		}
	}

	AVLNode<T, S> *sortedArrayToBST(AVLNode<T, S> *arr[], int start, int end, AVLNode<T, S> *root1)
	{
		/* Base Case */
		if (start > end)
			return NULL;

		/* Get the middle element and make it root */
		int mid = (start + end) / 2;
		/* maybe create new node with key, data, father*/
		// AVLNode<T, S> *root = new AVLNode<T, S>(arr[mid]->key, arr[mid]->data, root1);
		AVLNode<T, S> *root = arr[mid]; // almog change
		root->father = root1;			// almog change
		/* Recursively construct the left subtree and make it
		left child of root */
		root->left = sortedArrayToBST(arr, start, mid - 1, root);

		/* Recursively construct the right subtree and make it
		right child of root */
		root->right = sortedArrayToBST(arr, mid + 1, end, root);

		return root;
	}

	void fixHeight(AVLNode<T, S> *root)
	{
		if (root->left)
		{
			fixHeight(root->left);
		}
		else if (root->right)
		{
			fixHeight(root->right);
		}
		else
		{
			root->height = 0;
			return;
		}
		setHeight(root);
	}

	AVLTree<T, S> *combineTree(AVLTree<T, S> *tree1, AVLTree<T, S> *tree2)
	{
		AVLNode<T, S> *new_root = mergeTrees(tree1->getRoot(), tree2->getRoot(), tree1->getNumOfNode(), tree2->getNumOfNode());
		AVLTree<T, S> *res_tree = new AVLTree(new_root);
		res_tree->setNumOfNode(tree1->getNumOfNode() + tree2->getNumOfNode());
		fixHeight(res_tree->root);
		return res_tree;
	}
};
#endif