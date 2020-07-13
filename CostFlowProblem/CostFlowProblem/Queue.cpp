#include "Queue.h"


Queue::Queue()
{
	this->head = 1;
	this->tail = 0;
	for (int i = 0; i < MAX_SIZE; i++)
		this->data[i] = nullptr;
}


Queue::~Queue()
{
	for (int i = 0; i < MAX_SIZE; i++)
		delete this->data[i];
}

void Queue::MakeEmpty()
{
	head = 1;
	tail = 0;
}

bool Queue::isEmpty()
{
	return (AddOne(tail) == head);
}

int* Queue::front()
{
	if (isEmpty())
	{
		cout << "Error: Queue IS EMPTY :(" << endl;
		exit(1);
	}
	return (data[head]);


}

void Queue::EnQueue(int* item)
{
	if (AddOne(AddOne(tail)) == head)
	{
		cout << "Oh no!! Queue IS Full :(" << endl;
		exit(2);
	}
	tail = AddOne(tail);
	data[tail] = item;
}

int* Queue::DeQueue()
{
	int* item;

	if (isEmpty())
	{
		cout << "Error: Queue IS EMPTY :(" << endl;
		exit(3);
	}
	item = data[head];
	head = AddOne(head);
	return item;
}

int Queue::AddOne(int x)
{
	return ((1 + x) % MAX_SIZE);
}