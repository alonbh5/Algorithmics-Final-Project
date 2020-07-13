
#include "List.h"

List::List()
{
	MakeEmpty();
}

void List::MakeEmpty()
{
	Head = nullptr;
	Tail = nullptr;
}

bool List::IsEmpty()
{
	return (Head == nullptr);
}

void List::InsertToTail(int data)
{
	Node* newNode = new Node(nullptr, data);
	if (IsEmpty())
	{
		Head = newNode;
	}
	else
	{
		Tail->next = newNode;
	}
	Tail = newNode;
}

void List::InsertToHead(int data)
{
	Node* newNode = new Node(nullptr, data);
	if (IsEmpty())
	{
		Head = newNode;
		Tail = newNode;
	}
	else
	{
		newNode->next = Head;
		Head = newNode;
	}
}




//add function