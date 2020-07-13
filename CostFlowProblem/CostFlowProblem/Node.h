#ifndef _NODE_H
#define _NODE_H
#pragma warning (disable:4996)
#include <iostream>

class Node
{
	int data;
	Node* next;

	Node();
	Node(Node* ptr, int item);
	InsertAfter(Node* newnode);
	DeleteAfter();


};

#endif // !_NODE_H