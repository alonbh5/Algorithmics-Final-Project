#ifndef _LIST_H
#define _LIST_H
#pragma warning (disable:4996)

#include <iostream>
#include "Node.h"

class List
{
private:
	Node* m_Head;
	Node* m_Tail;

public:
	List();
	~List();
	bool IsEmpty();
	void MakeEmpty();
	void InsertToTail(int data);
	void InsertToHead(int data);
	Node* GetHead();
	Node* GetTail();
	void PrintList();
};


#endif // !_LIST_H