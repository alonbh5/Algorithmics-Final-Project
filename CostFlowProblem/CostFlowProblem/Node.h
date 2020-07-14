#ifndef _NODE_H
#define _NODE_H
#pragma warning (disable:4996)
#include <iostream>

class Node
{
public:
	int m_Data;
	Node* m_Next;

public:
	Node(int i_Item);
	Node(Node* i_Ptr, int i_Item);
	~Node();
	void InsertAfter(Node* newnode);
	Node* DeleteAfter();
};

#endif // !_NODE_H