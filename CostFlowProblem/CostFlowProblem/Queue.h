#ifndef _QUEUE_H
#define _QUEUE_H

#include "Node.h"
#include <iostream>
#include <stdlib.h>
using namespace std;
#pragma warning (disable: 4996)

const int DUMMY = -1;

class Queue
{
private:
	Node* m_Head;
	Node* m_Tail;

public:
	Queue();
	~Queue();
	void MakeEmpty();
	bool IsEmpty() const ;
	int Front() const;
	void EnQueue(const int i_Item);
	int DeQueue(); 

/*private:
	int m_Head;
	int m_Tail;
	int* m_Data; 
	int m_MaxSize;

private: 
	int AddOne(int x);

public:
	Queue(const int i_MaxSize);
	~Queue();
	void MakeEmpty();
	bool IsEmpty();
	int Front();
	void EnQueue(const int i_Item);
	int DeQueue();*/
};

#endif // !_QUEUE_H