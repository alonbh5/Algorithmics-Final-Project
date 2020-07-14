
#include "List.h"

List::List()
{
	MakeEmpty();
}

List::~List()
{
	if (!this->IsEmpty())
	{
		Node* currNode = m_Head;
		Node* nextNode = nullptr;
		while (currNode->m_Next)
		{
			nextNode = currNode->m_Next;
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

bool List::IsEmpty()
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
		m_Tail->m_Next = newNode;
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
		newNode->m_Next = m_Head;
		m_Head = newNode;
	}
}

Node* List::GetHead()
{
	return m_Head;
}

Node* List::GetTail()
{
	return m_Tail;
}

void List::PrintList()
{
	Node* currNode = m_Head;
	while (currNode)
	{
		std::cout << " " << currNode->m_Data;
		currNode = currNode->m_Next;
	}
	std::cout << ".";
}



//add function

ostream& operator<<(ostream& os, const List& obj)
{
	
	Node* currNode = obj.m_Head;
	while(currNode)
	{
		os << *currNode << " ";
		currNode = currNode->m_Next;
	}
		return os;
}
