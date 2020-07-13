#ifndef _LIST_H
#define _LIST_H
#pragma warning (disable:4996)

#include <iostream>
#include "Node.h"

class List
{
	Node* Head;
	Node* Tail;

public:
	List();
	bool IsEmpty();
	void MakeEmpty();
	void InsertToTail(int data);

};


#endif // !_LIST_H