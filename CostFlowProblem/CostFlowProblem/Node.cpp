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
