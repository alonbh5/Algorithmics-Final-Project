#ifndef _QUEUE_H
#define _QUEUE_H

#include <iostream>
#include <stdlib.h>
using namespace std;

#pragma warning (disable: 4996)

const int MAX_SIZE = 2050;


class Queue
{

private:
	int head;
	int tail;
	int* data[MAX_SIZE];

	static int AddOne(int x);

public:

	//ctor
	Queue();
	~Queue();

	void MakeEmpty();
	bool isEmpty();
	int* front();
	void EnQueue(int* item);
	int* DeQueue();


};

#endif // !_QUEUE_H