#include "Node.h"

Node::Node(int i_Item)
{
	m_Data = i_Item;
	m_Next = nullptr;
}

Node::Node(Node* i_Ptr, int i_Item)
{
	m_Data = i_Item;
	m_Next = i_Ptr;
}


Node::~Node()
{
	m_Next = nullptr;
}

int Node::GetData()
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
	return(temp);
}

ostream& operator<<(ostream& os, const Node& obj)
{
	os << obj.m_Data;
	return os;
}
