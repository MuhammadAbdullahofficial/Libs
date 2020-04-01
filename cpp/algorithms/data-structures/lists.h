#pragma once
#ifndef LISTS_F
#define LISTS_F
#include "nodes.h"
#include <iostream>
template<class t>
__interface List
{
	virtual void add(t value);
	virtual void remove(t value);
	virtual void clear();
	virtual int size()const;
	virtual t get(unsigned int index)const;
	virtual int index_of(t value);
	virtual bool exist(t value)const;

};

template<class t>
class LinkedList_s : public List<t>
{
public:

	LinkedList_s() :head(null), nodes(0) {}
	LinkedList_s(std::initializer_list<t> init) :head(0), nodes(0) { this->operator=(init); }
	LinkedList_s(LinkedList_s& init) :head(0), nodes(0) { this->operator=(init); }
	void operator=(std::initializer_list<t> list) { clear(); for (t node : list) { this->add(node); } }
	void operator=(LinkedList_s& list) { clear(); merge_internal(list.head); }
	void operator+=(std::initializer_list<t> list) { for (t node : list) { this->add(node); } };
	void operator+=(LinkedList_s<t>& list) { merge_internal(list.head); };
	bool operator==(LinkedList_s& list) {
		if (nodes != list.nodes)return false;
		auto trav = head;
		auto trav2 = list.head;
		while (trav != null && trav2 != null)
		{
			if (trav->data != trav2->data)return false;
			trav = trav->link;
			trav2 = trav2->link;
		}
		return true;
	}

	t& operator[](unsigned int index) {
		if (index >= nodes || index < 0)return head->data;
		else {
			auto trav = head;
			for (unsigned int i = 0; i < index; i++)
				trav = trav->link;
			return trav->data;
		}
	}

	void add(t value) {
		if (head == null) { head = new SingleLinkNode<t>(value); }
		else { auto traverse = head; while (traverse->link != null) traverse = traverse->link; traverse->link = new SingleLinkNode<t>(value); }
		nodes += 1;
	}

	void remove(t value) {
		if (head == null)return;
		if (head->data == value) {
			if (nodes == 1) { delete head; head = null; }
			else {
				auto link = head;
				head = head->link;
				delete link;
			}
			nodes -= 1;
		}
		else {
			auto traverse = head;
			while (traverse->link->link != null && traverse->link->data != value)
				traverse = traverse->link;
			if (traverse == null)return;
			if (traverse->link->data != value)return;
			if (traverse->link->link == null) { delete traverse->link; traverse->link = null; }
			else {
				auto temp = traverse->link;
				traverse->link = traverse->link->link;
				delete temp;
				nodes -= 1;
			}
		}
	}

	void clear() {
		SingleLinkNode<t>* node = head;
		while (head != null)
		{
			node = node->link;
			delete head;
			head = node;
		}
		nodes = 0;
	}

	int size()const { return nodes; }

	bool exist(t value)const {
		auto tra = head;
		while (tra != null)
		{
			if (tra->data == value) { return true; }
			tra = tra->link;
		}
		return false;
	}

	t get(unsigned int index)const {
		if (index >= nodes || index < 0)return rand();
		else {
			auto trav = head;
			for (unsigned int i = 0; i < index; i++)
				trav = trav->link;
			return trav->data;
		}
	}

	int index_of(t value) {
		auto trav = head;
		for (int i = 0; i < nodes; i++)
		{
			if (trav->data == value)return i;
			trav = trav->link;
		}
		return -1;
	}

	LinkedList_s<t>& clone() {
		LinkedList_s<t>* copy = new LinkedList_s<t>();
		auto trav = head;
		while (trav != null)
		{
			copy->add(trav->data);
			trav = trav->link;
		}
		return *copy;
	}

	void print() {
		auto tra = head;
		while (tra != null)
		{
			std::cout << tra->data << ' ';
			tra = tra->link;
		}
		std::cout << std::endl;
	}

	~LinkedList_s()
	{
		clear();
	}

private:
	SingleLinkNode<t>* head;
	int nodes;

	void merge_internal(SingleLinkNode<t>* list) {
		while (list)
		{
			this->add(list->data);
			list = list->link;
		}
	}

};




#endif // !LISTS_F
