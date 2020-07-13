#ifndef _QUEUE_H
#define _QUEUE_H

#include <iostream>
#include <stdlib.h>
using namespace std;

#pragma warning (disable: 4996)

const int MAX_SIZE = 1000;

class Queue
{

private:
	int m_Head;
	int m_Tail;
	int* m_Data[MAX_SIZE]; //change to num of vertex

	static int AddOne(int x);

public:

	//ctor
	Queue();
	~Queue();

	void MakeEmpty();
	bool isEmpty();
	int* Front();
	void EnQueue(int* item);
	int* DeQueue();


};

#endif // !_QUEUE_H