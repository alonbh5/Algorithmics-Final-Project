#ifndef _LIST_H_
#define _LIST_H_
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
	~List();
	bool IsEmpty() const;
	void MakeEmpty();
	void InsertToTail(int data);
	void InsertToHead(int data);
	Node* GetHead() const;
	Node* GetTail() const;
	friend ostream& operator<<(ostream& os, const List& obj);
};


#endif // !_LIST_H_