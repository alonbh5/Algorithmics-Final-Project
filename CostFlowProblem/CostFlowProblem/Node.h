#ifndef _NODE_H
#define _NODE_H
#pragma warning (disable:4996)
#include <iostream>

class Node
{
	int data;
	Node* next;

public:
	Node();
	~Node();
	Node(Node* ptr, int item);
	void InsertAfter(Node* newnode);
	Node* DeleteAfter();
};

#endif // !_NODE_H