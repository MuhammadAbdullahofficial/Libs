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

#endif // !NODES_F
