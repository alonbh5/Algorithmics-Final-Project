#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "Node.h"
#include <iostream>
#include <stdlib.h>
//#pragma warning (disable: 4996)

class Queue
{
private:
	const int DUMMY = -1;
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
};

#endif // !_QUEUE_H_