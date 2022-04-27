#pragma once

#ifndef LIST_H
#define LIST_H

#include <iostream>


template <class T>
class Node {
public:
	int key;
	T data;
	Node* next;
	Node(int key, T data, Node<T>* next) :
		key(key), data(data), next(next) {};
	~Node() = default;
};

template <class T>
class LinkedList {
public:
	Node<T>* head;

	LinkedList() : head(nullptr) {};

	~LinkedList()
	{
		Node<T>* curr_node = head;
		while (curr_node != nullptr)
		{
			Node<T>* next_node = curr_node->next;
			delete curr_node;
			curr_node = next_node;
		}
		head = nullptr;
	}

	void deleteListAndData()
	{
		Node<T>* curr_node = head;
		while (curr_node != nullptr)
		{
			Node<T>* next_node = curr_node->next;
			delete curr_node->data;
			delete curr_node;
			curr_node = next_node;
		}
		head = nullptr;
	}

	void removeNode(const int& key)
	{
		Node<T>* node = head;
		if (key == head->key)
		{
			head = head->next;
		}
		else
		{
			node = head->next;
			Node<T>* prev_node = head;
			while (node != nullptr)
			{
				if (node->key == key)
				{
					prev_node->next = node->next;
					break;
				}
				prev_node = node;
				node = node->next;
			}
		}
		delete node;
	}

	Node<T>* insertNode(const int& key, const T& data)
	{
		Node<T>* new_node = new Node<T>(key, data, nullptr);
		// First insert
		if (head == nullptr)
		{
			head = new_node;
		}
		else
		{
			new_node->next = head;
			head = new_node;
		}
		return new_node;
	}

	T getValue(const int& key)
	{
		Node<T>* node = head;
		while (node != nullptr)
		{
			if (key == node->key) return node->data;
			node = node->next;
		}
		return NULL;
	}

};

#endif //LIST_H