#include <iostream>
#pragma once
#ifndef TREES_F
#define TREES_F
#include "nodes.h"
template<class t>
__interface Tree
{
public:
	virtual void add(t value);
	//virtual void remove(t value);
	virtual bool exist(t value);
	virtual void clear();
	virtual int size()const;
};

template<class t>
class BinaryTree : public Tree<t>
{
public:

	BinaryTree() :root(null), nodes(0) {}
	BinaryTree(std::initializer_list<t> init) :root(null), nodes(0) { for (t node : init) { this->add(node); } }
	void operator=(std::initializer_list<t> list) { clear(); for (t node : list) { this->add(node); } }
	void operator=(BinaryTree& tree) { clear(); merge_internal(tree.root); }
	void operator+=(std::initializer_list<t> list) { for (t node : list) { this->add(node); } };
	void operator+=(BinaryTree<t>& tree) { merge_internal(tree.root); };


	void add(t value) {
		if (!root) {
			root = new DoubleLinkNode<t>(value);
			nodes += 1;
		}
		else
		{
			DoubleLinkNode<t>* tra = root;
			while (tra != null)
			{
				if (tra->data == value) { return; }
				else if (tra->data > value) {
					if (tra->p_link == null)
					{
						tra->p_link = new DoubleLinkNode<t>(value);
						nodes += 1;
						return;
					}
					else
						tra = tra->p_link;
				}
				else if (tra->data < value) {
					if (tra->n_link == null)
					{
						tra->n_link = new DoubleLinkNode<t>(value);
						nodes += 1;
						return;
					}
					else
						tra = tra->n_link;
				}
			}
		}
	}

	
	bool exist(t value) { return get_node_internal(root, value) == null ? false : true; }
	int size()const { return nodes; }
	void clear() { clear_internal(root); root = null; nodes = 0; }
	~BinaryTree(){ clear(); }

	/**///---------------------------------------///**/temparary validation code
	/**/void print(DoubleLinkNode<t>* n) {  	 ///**/
	/**/	if (n == null)return;				 ///**/
	/**/	print(n->p_link);					 ///**/
	/**/	std::cout << n->data << ' ';		 ///**/
	/**/	print(n->n_link);					 ///**/
	/**/}										 ///**/
	/**/void print() {							 ///**/
	/**/	print(root);						 ///**/
	/**/}										 ///**/
	/**///---------------------------------------///**/

private:
	DoubleLinkNode<t>* root;
	unsigned int nodes;

	void clear_internal(DoubleLinkNode<t>* node) {
		if (node == null)return;
		clear_internal(node->p_link);
		DoubleLinkNode<t>* node_n = node->n_link;
		delete node;
		node = null;
		clear_internal(node_n);
	}

	DoubleLinkNode<t>* get_node_internal(DoubleLinkNode<t>* node, t value) {
		if (node == null)return null;
		else if (node->data == value)return node;
		else if (node->data > value)return get_node_internal(node->p_link, value);
		else if (node->data < value)return get_node_internal(node->n_link, value);
		else return null;
	}

	DoubleLinkNode<t>* get_node_parent_internal(DoubleLinkNode<t>* node, t value) {
		if (node == null)return null;
		else if (node->n_link->data == value || 
			node->p_link->data == value)return node;
		else if (node->data > value)return get_node_parent_internal(node->p_link, value);
		else if (node->data < value)return get_node_parent_internal(node->n_link, value);
		else return null;
	}

	void merge_internal(DoubleLinkNode<t>* node) {
		if (node == null)return;
		else {
			merge_internal(node->p_link);
			this->add(node->data);
			merge_internal(node->n_link);
		}
	}

	void connect_subtree_internal(DoubleLinkNode<t>* main, DoubleLinkNode<t> * sub) {
		if (main == null) { return; }
		else if (main->data == sub->data) { return; }
		else if (main->data > sub->data&& main->p_link != null) { connect_subtree_internal(main->p_link, sub); }
		else if (main->data > sub->data&& main->p_link == null) { main->p_link = sub; nodes += subtree_size_internal(sub);  return; }
		else if (main->data < sub->data&& main->n_link != null) { connect_subtree_internal(main->n_link, sub);}
		else if (main->data < sub->data&& main->n_link == null) { main->n_link = sub; nodes += subtree_size_internal(sub);  return; }
	}

	int subtree_size_internal(DoubleLinkNode<t>* node) {
		if (node == null)return 0;
		else if (node->n_link == null && node->p_link == null)return 1;
		else return 1 + subtree_size_internal(node->p_link) + subtree_size_internal(node->n_link);
	}

};

#endif // !TREES_F
