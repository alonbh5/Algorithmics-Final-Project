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
	List(const List& i_Other) = delete; // NEED???
	~List();
	bool IsEmpty() const;
	void MakeEmpty();
	void InsertToTail(int data);
	void InsertToHead(int data);
	Node* GetHead() const;
	Node* GetTail() const;
	friend ostream& operator<<(ostream& os, const List& obj);
};


#endif // !_LIST_H