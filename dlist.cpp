
#include <iostream>
#include "pch.h"
#include "dlist.hpp"

using namespace std;
template <typename T>
dlinklist<T>::dlinklist()
{
	this->_size = 0;
	this->head = nullptr;
	this->tail = nullptr;
}

template <typename T>
dlinklist<T>::~dlinklist()
{

}


template <typename T>
void dlinklist<T>::push_front(T value)
{
	dlinklist_node_t<T>* node_tmp = new dlinklist_node_t<T>;
	node_tmp->data = value;
	node_tmp->prev = nullptr;
	node_tmp->next = nullptr;

	if (head == nullptr)
	{
		head = node_tmp;
		tail = node_tmp;
	}
	else
	{
		head->prev = node_tmp;
		node_tmp->next = head;
		head = node_tmp;
	}

	this->_size++;
}

template <typename T>
void dlinklist<T>::push_back(T value)
{
	dlinklist_node_t<T>* node_tmp = new dlinklist_node_t<T>;
	node_tmp->data = value;
	node_tmp->prev = nullptr;
	node_tmp->next = nullptr;


	if (tail == nullptr)
	{
		head = node_tmp;
		tail = node_tmp;
	}
	else
	{
		tail->next = node_tmp;
		node_tmp->prev = tail;
		tail = node_tmp;

	}

	_size++;
}

template <typename T>
void dlinklist<T>::pop_front(void)
{
	if (!empty())
	{
		dlinklist_node_t<T>* node_tmp = head;

		if (head == tail)
		{
			tail = nullptr;
			head = nullptr;
		}
		else
		{
			head = head->next;
			head->prev = nullptr;
		}

		delete node_tmp;
		_size--;
	}
}

template<typename T>
void dlinklist<T>::pop_back(void)
{
	if (!empty())
	{
		dlinklist_node_t<T>* node_tmp = tail;

		if (tail == head)
		{
			tail = nullptr;
			head = nullptr;
		}
		else
		{
			tail = tail->prev;
			tail->prev = nullptr;
		}

		delete node_tmp;
		_size--;
	}
}

template <typename T>
T dlinklist<T>::front(void) { return head->data; }

template <typename T>
T dlinklist<T>::back(void) { return tail->head; }

template <typename T>
bool dlinklist<T>::empty(void)
{
	if (this->_size > 0)
		return false;
	return true;

}

template <typename T>
int dlinklist<T>::size(void)
{
	return this->_size;
}










//class dlinklist_iterator;


//dlinklist_iterator dlinklist<T>::insert(const dlinklist_iterator& pos, T value)
//{
//	dlinklist_node_t<T>* node_cur = pos.node();
//
//	if (node_cur == head)
//		push_front(value);
//	else if (node_cur == tail->next)
//		push_back(value);
//	else
//	{
//		dlinklist_node_t<T>* node_tmp = new dlinklist_node_t<T>;
//		node_tmp->data = value;
//		node_tmp->next = node_cur->next;
//		node_tmp->prev = node_cur;
//		node_cur->next = node_tmp;
//		node_cur->next->prev = node_tmp;
//	}
//
//	this->_size++;
//	return pos;
//};
//
//
//dlinklist_iterator erase(dlinklist_iterator pos)
//{
//	dlinklist_node_t<T>* node_cur = pos.node();
//
//	if (!empty())
//	{
//		if (node_cur == head)
//			pop_front();
//		else if (node_cur == tail->next)
//			pop_back();
//		else
//		{
//			node_cur->next->prev = node_cur->prev;
//			node_cur->prev->next = node_cur->next;
//			delete node_cur;
//		}
//	}
//	this->_size--;
//	return pos;
//};
//
//void display_list() { //display list leci od head do tail jak w stl
//
//	dlinklist_node_t<T> *node_tmp = head;
//	for (int i = 0; i < _size; i++) {
//		cout << node_tmp->data << endl;
//		node_tmp = node_tmp->next;
//		if (node_tmp == nullptr)cout << "poza lista" << endl;
//	}
//}