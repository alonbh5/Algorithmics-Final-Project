#ifndef _QUEUE_H
#define _QUEUE_H

#include <iostream>
#include <stdlib.h>
using namespace std;
#pragma warning (disable: 4996)

class Queue
{
private:
	int m_Head;
	int m_Tail;
	int* m_Data; 
	int m_MaxSize;

private: 
	int AddOne(int x);

public:
	Queue(int i_MaxSize);
	~Queue();
	void MakeEmpty();
	bool isEmpty();
	int Front();
	void EnQueue(int i_Item);
	int DeQueue();
};

#endif // !_QUEUE_H