#pragma once
#ifndef LISTS_F
#define LISTS_F
#include "nodes.h"
#include <iostream>
template<class t>
class List
{
public:
	
	virtual void add(t value) = 0;
	virtual void remove(t value) = 0;
	virtual void clear() = 0;
	virtual int size()const = 0;
	virtual t get(unsigned int index)const = 0;
	virtual int index_of(t value) = 0;
	virtual bool exist(t value)const = 0;
	virtual ~List() {};
};

template<class t>
class LinkedList_s : public List<t>
{
public:

	LinkedList_s() :head(null), nodes(0) {}
	LinkedList_s(std::initializer_list<t> init) :head(null), nodes(0) { this->operator=(init); }
	LinkedList_s(LinkedList_s& init) :head(null), nodes(0) { this->operator=(init); }
	void operator=(std::initializer_list<t> list) { clear(); for (t node : list) { this->add(node); } }
	void operator=(LinkedList_s& list) { clear(); merge_internal(list.head); }
	void operator+=(std::initializer_list<t> list) { for (t node : list) { this->add(node); } };
	void operator+=(LinkedList_s<t>& list) { merge_internal(list.head); };
	bool operator==(LinkedList_s& list) {
		if (nodes != list.nodes)return false;
		SingleLinkNode<t>* trav = head;
		SingleLinkNode<t>* trav2 = list.head;
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
			SingleLinkNode<t>* trav = head;
			for (unsigned int i = 0; i < index; i++)
				trav = trav->link;
			return trav->data;
		}
	}

	void add(t value) {
		if (head == null) { head = new SingleLinkNode<t>(value); }
		else { SingleLinkNode<t>* traverse = head; while (traverse->link != null) traverse = traverse->link; traverse->link = new SingleLinkNode<t>(value); }
		nodes += 1;
	}

	void remove(t value) {
		if (head == null)return;
		if (head->data == value) {
			if (nodes == 1) { delete head; head = null; }
			else {
				SingleLinkNode<t>* link = head;
				head = head->link;
				delete link;
			}
			nodes -= 1;
		}
		else {
			SingleLinkNode<t>* traverse = head;
			while (traverse->link->link != null && traverse->link->data != value)
				traverse = traverse->link;
			if (traverse == null)return;
			if (traverse->link->data != value)return;
			if (traverse->link->link == null) { delete traverse->link; traverse->link = null; }
			else {
				SingleLinkNode<t>* temp = traverse->link;
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
		SingleLinkNode<t>* tra = head;
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
			SingleLinkNode<t>* trav = head;
			for (unsigned int i = 0; i < index; i++)
				trav = trav->link;
			return trav->data;
		}
	}

	int index_of(t value) {
		SingleLinkNode<t>* trav = head;
		for (int i = 0; i < nodes; i++)
		{
			if (trav->data == value)return i;
			trav = trav->link;
		}
		return -1;
	}

	void print() {
		SingleLinkNode<t>* tra = head;
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

template<class t>
class LinkedList_d : public List<t>
{
public:
	LinkedList_d() :head(null), tail(null), nodes(0) {}
	LinkedList_d(std::initializer_list<t> init) :head(null), tail(null), nodes(0) { this->operator=(init); }
	LinkedList_d(LinkedList_d& init) :head(null), tail(null), nodes(0) { this->operator=(init); }
	void operator=(std::initializer_list<t> list) { clear(); for (t node : list) { this->add(node); } }
	void operator=(LinkedList_d& list) { clear(); merge_internal(list.head); }
	void operator+=(std::initializer_list<t> list) { for (t node : list) { this->add(node); } };
	void operator+=(LinkedList_s<t>& list) { merge_internal(list.head); };
	bool operator==(LinkedList_d& list) {
		if (nodes != list.nodes)return false;
		DoubleLinkNode<t>* trav2 = list.head;
		DoubleLinkNode<t>* trav = head;
		while (trav != null && trav2 != null)
		{
			if (trav->data != trav2->data)return false;
			trav = trav->n_link;
			trav2 = trav2->n_link;
		}
		return true;
	}
	t& operator[](unsigned int index) {
		if (index >= nodes || index < 0)return head->data;
		else {
			DoubleLinkNode<t>* trav = head;
			for (unsigned int i = 0; i < index; i++)
				trav = trav->n_link;
			return trav->data;
		}
	}

	void add(t value) {
		if (head == null) { tail = head = new DoubleLinkNode<t>(value); }
		else { auto node = new DoubleLinkNode<t>(value, tail, null); tail->n_link = node; tail = node; }
		nodes += 1;
	}

	void remove(t value) {
		if (head == null)return;
		if (head->data == value) {
			if (nodes == 1) { delete head; head = null; }
			else {
				auto link = head;
				head = head->n_link;
				head->p_link = null;
				delete link;
			}
			nodes -= 1;
		}
		else {
			DoubleLinkNode<t>* traverse = head;
			while (traverse != null)
			{
				if (traverse->data == value)break;
				traverse = traverse->n_link;
			}
			if (traverse == null)return;
			if (traverse->n_link == null) {
				traverse->p_link->n_link = null;
				delete traverse;
			}
			else {
				traverse->p_link->n_link = traverse->n_link;
				traverse->n_link->p_link = traverse->p_link;
				delete traverse;
			}
			nodes -= 1;
		}
	}

	void clear() {
		DoubleLinkNode<t>* node = head;
		while (node != null)
		{
			head = node->n_link;
			delete node;
			node = head;
		}
		head = tail = null;
		nodes = 0;
	}

	int size()const { return nodes; }

	bool exist(t value)const {
		auto tra = head;
		while (tra != null)
		{
			if (tra->data == value) { return true; }
			tra = tra->n_link;
		}
		return false;
	}

	t get(unsigned int index)const {
		if (index >= nodes || index < 0)return rand();
		else {
			auto trav = head;
			for (unsigned int i = 0; i < index; i++)
				trav = trav->n_link;
			return trav->data;
		}
	}

	int index_of(t value) {
		auto trav = head;
		for (int i = 0; i < nodes; i++)
		{
			if (trav->data == value)return i;
			trav = trav->n_link;
		}
		return -1;
	}

	void print() {
		auto tra = head;
		while (tra != null)
		{
			std::cout << tra->data << ' ';
			tra = tra->n_link;
		}
		std::cout << std::endl;
	}

	~LinkedList_d()
	{
		clear();
	}

private:
	DoubleLinkNode<t>* head;
	DoubleLinkNode<t>* tail;
	int nodes;

	void merge_internal(DoubleLinkNode<t>* list) {
		while (list)
		{
			this->add(list->data);
			list = list->n_link;
		}
	}
};

class list
{
public:
	list():head(null), nodes(0){}

	template<class t>
	void add(t data) {
		if (head == null) { head = new SingleDataNode<t>(data); }
		else { SingleLinkNode_g* trav = head; while (trav->link)trav = trav->link; trav->link = new SingleDataNode<t>(data); }
		nodes += 1;
	}

	void clear() {
		SingleLinkNode_g* trav = head;
		while (trav)
		{
			head = trav->link;
			delete trav;
			trav = head;
		}
		nodes = 0;
	}
	template<class t>
	void get(unsigned int index, t& data_var) {
		try
		{
			if (index >= nodes || index < 0)return;
			SingleLinkNode_g* trav = head;
			for (int i = 0; i < index; i++)
				trav = trav->link;
			data_var = ((SingleDataNode<t>*)trav)->data;
		}
		catch (const std::exception& e)
		{
			std::cerr << "error\n";
		}
	}
	~list()
	{
		clear();
	}

private:
	SingleLinkNode_g* head;
	int nodes;
};



#endif // !LISTS_F
