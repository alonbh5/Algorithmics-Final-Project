#ifndef _NODE_H
#define _NODE_H
#pragma warning (disable:4996)
#include <iostream>

class Node
{
public:
	int data;
	Node* next;

	Node();
	~Node();
	Node(Node* ptr, int item);
	void InsertAfter(Node* newnode);
	Node* DeleteAfter();
};

#endif // !_NODE_H