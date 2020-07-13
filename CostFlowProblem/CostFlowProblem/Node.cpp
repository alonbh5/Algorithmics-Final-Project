#include "Node.h"

Node::Node()
{
	next = nullptr;
}

Node::~Node()
{
	next = nullptr;
}

Node::Node(Node* ptr, int item)
{
	data = item;
	next = ptr;

}

Node::InsertAfter(Node* newnode)
{
	newnode->next = next;
	next = newnode;
}

Node::DeleteAfter()
{
	Node* temp = next;
	if (next == nullptr)
	{
		return nullptr;
	}
	return(temp);
}
