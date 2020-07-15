
#include "List.h"

List::List()
{
	MakeEmpty();
}

List::~List()
{
	// in book 
	if (!this->IsEmpty())
	{
		Node* currNode = m_Head;
		Node* nextNode = nullptr;
		while (currNode->GetNext())
		{
			nextNode = currNode->GetNext();
			delete currNode;
			currNode = nextNode;
		}
		if (currNode)
		{
			delete currNode;
		}
	}

}

void List::MakeEmpty()
{
	m_Head = nullptr;
	m_Tail = nullptr;
}

bool List::IsEmpty() const
{
	return (m_Head == nullptr);
}

void List::InsertToTail(int data)
{
	Node* newNode = new Node(nullptr, data);
	if (IsEmpty())
	{
		m_Head = newNode;
	}
	else
	{
		m_Tail->SetNext(newNode);
	}
	m_Tail = newNode;
}

void List::InsertToHead(int data)
{
	Node* newNode = new Node(nullptr, data);
	if (IsEmpty())
	{
		m_Head = newNode;
		m_Tail = newNode;
	}
	else
	{
		newNode->SetNext(m_Head);
		m_Head = newNode;
	}
}

Node* List::GetHead() const
{
	return m_Head;
}

Node* List::GetTail() const
{
	return m_Tail;
}

//add 
ostream& operator<<(ostream& os, const List& obj) 
{
	Node* currNode = obj.m_Head;
	while(currNode)
	{
		if(currNode->GetNext())
			os << *currNode << ", ";
		else
			os << *currNode << ".";
		currNode = currNode->GetNext();
	}
	return os;
}
