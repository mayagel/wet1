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
	int rank;
	int height;
	AVLNode *left;
	AVLNode *right;
	AVLNode *father;
	AVLNode(){};// Yagel added empty default constructor 
	AVLNode(const D &key, const C &data, AVLNode *father) : key(key), data(data), rank(1), height(0), left(nullptr), right(nullptr), father(father){};
	~AVLNode() = default;
	AVLNode<C, D> *getRight(){return right;} 
	AVLNode<C, D> *getLeft(){return left;} 
};

template <class T, class S>
class AVLTree
{
private:
	AVLNode<T, S> *root;
	int num_of_nodes; //added by yagel 06.06

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
			updateRank(node);
			setHeight(node);
			node = node->father;
		}
	}

	void updateRank(AVLNode<T, S> *node)
	{
		int node_left_rank = node->left == nullptr ? 0 : node->left->rank;
		int node_right_rank = node->right == nullptr ? 0 : node->right->rank;
		node->rank = node_left_rank + node_right_rank + 1;
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
		updateRank(node);
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
		updateRank(node);
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
		deleteTree(root);
		root = nullptr;
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

	//for testing
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
		num_of_nodes += 1; //added by yagel 06.06
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
				num_of_nodes -= 1; //added by yagel 06.06
				return;
			}
			else if (right_son_exist && !left_son_exist)
			{
				std::swap(root->key, root->right->key);
				std::swap(root->data, root->right->data);
				delete root->right;
				root->right = nullptr;
				setHeight(root);
				updateRank(root);
				num_of_nodes -= 1; //added by yagel 06.06
				return;
			}
			else if (left_son_exist && !right_son_exist)
			{
				std::swap(root->key, root->left->key);
				std::swap(root->data, root->left->data);
				delete root->left;
				root->left = nullptr;
				setHeight(root);
				updateRank(root);
				num_of_nodes -= 1; //added by yagel 06.06
				return;
			}
		}
		AVLNode<T, S> *father = removeFromBST(node, left_son_exist, right_son_exist);
		setHeight(father);
		balance(father);
		num_of_nodes -= 1; //added by yagel 06.06
	}

	AVLNode<T, S> *select(AVLNode<T, S> *node, int index)
	{
		if (!node)
		{
			return nullptr;
		}
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

	int getNumOfNode() { return num_of_nodes; } //added by yagel 06.06

	void getNumOfNode(int new_nums) {num_of_nodes = new_nums;}


// from here update by Yagel 02.05 00:14
	S *merge(int arr1[], int arr2[], int m, int n)
	{
    // mergedArr[] is going to contain result
    int *mergedArr = new int[m + n];
    int i = 0, j = 0, k = 0;
 
    // Traverse through both arrays
    while (i < m && j < n)
    {
        // Pick the smaller element and put it in mergedArr
        if (arr1[i] < arr2[j])
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
        i++; k++;
    }
 
    // If there are more elements in second array
    while (j < n)
    {
        mergedArr[k] = arr2[j];
        j++; k++;
    }
 
    return mergedArr;
}

	AVLNode<T, S>* mergeTrees(AVLNode<T, S> *root1, AVLNode<T, S> *root2, int length1, int length2)
{
    // Store inorder traversal of
    // first tree in an array arr1[]
    S *arr1 = new S[length1];
    int i = 0;
    storeInorder(root1, arr1, &i);
 
    // Store inorder traversal of second
    // tree in another array arr2[]
    S *arr2 = new S[length2];
    int j = 0;
    storeInorder(root2, arr2, &j);
 
    // Merge the two sorted array into one
    S *mergedArr = merge(arr1, arr2, length1, length2);
 
    // Construct a tree from the merged
    // array and return root of the tree
    return sortedArrayToBST (mergedArr, 0, length1 + length2 - 1);
}
	
	// A helper function that stores inorder
	// traversal of a tree rooted with node
	void storeInorder(AVLNode<T, S>* node, int inorder[], int *index_ptr)
	{
		if (node == NULL)
			return;
	
		/* first recur on left child */
		storeInorder(node->left, inorder, index_ptr);
	
		inorder[*index_ptr] = node->data;
		(*index_ptr)++; // increase index for next entry
	
		/* now recur on right child */
		storeInorder(node->right, inorder, index_ptr);
	}
 
	AVLNode<T, S>* sortedArrayToBST(int arr[], int start, int end)
	{
		/* Base Case */
		if (start > end)
		return NULL;
	
		/* Get the middle element and make it root */
		int mid = (start + end)/2;
		AVLNode<T, S> *root = new AVLNode<T, S>(arr[mid]);
	
		/* Recursively construct the left subtree and make it
		left child of root */
		root->left = sortedArrayToBST(arr, start, mid-1);
	
		/* Recursively construct the right subtree and make it
		right child of root */
		root->right = sortedArrayToBST(arr, mid+1, end);
	
		return root;
	}
	
	AVLTree<T, S>* combineTree(AVLTree<T, S>* tree1, AVLTree<T, S>* tree2){
		AVLNode<T, S>* new_root = mergeTrees(tree1->getRoot(), tree2->getRoot(), tree1->getNumOfNode(), tree2->getNumOfNode());
		AVLTree<T, S>* res_tree = new AVLTree(new_root);
		res_tree->getNumOfNode(tree1->getNumOfNode() + tree2->getNumOfNode());
		return res_tree;
	}
};
#endif