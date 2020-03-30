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
	virtual void remove(t value);
	virtual bool exist(t value);
	virtual int size()const;
};

template<class t>
class BinaryTree : public Tree<t>
{
public:
	BinaryTree() :root(null), nodes(0) {}

	void add(t value) {
		if (!root) {
			root = new DoubleLinkNode<t>(value);
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
						return;
					}
					else
						tra = tra->p_link;
				}
				else if (tra->data < value) {
					if (tra->n_link == null)
					{
						tra->n_link = new DoubleLinkNode<t>(value);
						return;
					}
					else
						tra = tra->n_link;
				}
			}
		}
	}
	void remove(t value) {
		
	}
	bool exist(t value) { return false; }
	int size()const { return 0; }

	~BinaryTree()
	{
	}

	//---------------------------------------
	//for validation temp               //*--
	void p(DoubleLinkNode<t>* n) {      //*--
		if (n == null)return;			//*--
		p(n->p_link);					//*--
		std::cout << n->data << ' ';	//*--
		p(n->n_link);					//*--
	}									//*--
										//*--
	void print() {						//*--
		p(root);						//*--
	}									//*--
	//---------------------------------------

private:
	DoubleLinkNode<t>* root;
	unsigned int nodes;
};

#endif // !TREES_F
