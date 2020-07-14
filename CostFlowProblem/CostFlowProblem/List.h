#ifndef _LIST_H
#define _LIST_H
#pragma warning (disable:4996)

#include <iostream>
#include "Node.h"

using namespace std;
class List
{
private:
	Node* m_Head;
	Node* m_Tail;

public:
	List();
	List(List& Other);
	~List();
	bool IsEmpty();
	void MakeEmpty();
	void InsertToTail(int data);
	void InsertToHead(int data);
	Node* GetHead();
	Node* GetTail();
	friend ostream& operator<<(ostream& os, const List& obj);

};


#endif // !_LIST_H