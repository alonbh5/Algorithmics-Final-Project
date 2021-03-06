#include "Node.h"

Node::Node(const int i_Item)
{
	m_Data = i_Item;
	m_Next = nullptr;
}

Node::Node(Node* i_Ptr, const int i_Item)
{
	m_Data = i_Item;
	m_Next = i_Ptr;
}

Node::~Node()
{
	m_Next = nullptr;
}

int Node::GetData() const
{
	return m_Data;
}

Node* Node::GetNext()
{
	return m_Next;
}

void Node::SetNext(Node* i_Ptr)
{
	m_Next = i_Ptr;
}

void Node::InsertAfter(Node* newnode)
{
	newnode->m_Next = m_Next;
	m_Next = newnode;
}

Node* Node::DeleteAfter()
{
	Node* temp = m_Next;
	if (m_Next == nullptr)
	{
		return nullptr;
	}
	m_Next = temp->m_Next;
	return(temp);
}

ostream& operator<<(ostream& i_os, const Node& i_obj)
{
	i_os << i_obj.m_Data;
	return i_os;
}
