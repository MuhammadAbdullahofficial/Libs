#pragma once
#ifndef NODES_F
#define NODES_F
#define null nullptr
template<class t>
struct SingleLinkNode
{
	t data;
	SingleLinkNode* link;
	SingleLinkNode(t val) :data(val), link(null) {}
	SingleLinkNode(t val, SingleLinkNode* lnk) :data(val), link(lnk) {}
};
template<class t>
struct DoubleLinkNode
{
	t data;
	DoubleLinkNode* p_link;
	DoubleLinkNode* n_link;
	DoubleLinkNode(t val) :data(val), p_link(null), n_link(null) {}
	DoubleLinkNode(t val, DoubleLinkNode* p, DoubleLinkNode* n) :data(val), p_link(p), n_link(n) {}
};
template<class t>
struct MultiLinkNode
{
	t data;
	unsigned int links_size;
	MultiLinkNode** links;
	MultiLinkNode(t val) :data(val), links(null) {}
	MultiLinkNode(t val, MultiLinkNode** lnks, unsigned int size) :data(val), links(lnks), links_size(size) {}
};

struct SingleLinkNode_g
{
	SingleLinkNode_g* link;	
	virtual ~SingleLinkNode_g() {}
};

struct DoubleLinkNode_g
{
	DoubleLinkNode_g* n_link;
	DoubleLinkNode_g* p_link;
	virtual ~DoubleLinkNode_g() {}
};

struct MultiLinkNode_g
{
	unsigned int links_size;
	MultiLinkNode_g** links;
	virtual ~MultiLinkNode_g() {}
};

template<class t>
struct SingleDataNode : public SingleLinkNode_g
{
	t data;
	SingleDataNode(t val) :data(val) { link = null; }
	SingleDataNode(t val, SingleLinkNode_g* lnk) :data(val) { link = lnk; }
};

template<class t>
struct DoubleDataNode : public DoubleLinkNode_g
{
	t data;
	DoubleDataNode(t val) :data(val) { p_link = n_link = null; }
	DoubleDataNode(t val, DoubleLinkNode_g* n_lnk, DoubleLinkNode_g* p_lnk) :data(val) { n_link = n_lnk; p_link = p_lnk; }
};

template<class t>
struct MultiDataNode : public MultiLinkNode_g
{
	t data;
	MultiDataNode(t val) :data(val) { links = null; }
	MultiDataNode(t val, MultiLinkNode_g** lnks) :data(val) { links = lnks; }
};

#endif // !NODES_F
