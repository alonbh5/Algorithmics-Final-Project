#include "Queue.h"


Queue::Queue()
{
	this->m_Head = 1;
	this->m_Tail = 0;
	for (int i = 0; i < MAX_SIZE; i++)
		this->m_Data[i] = nullptr;
}


Queue::~Queue()
{
	for (int i = 0; i < MAX_SIZE; i++)
		delete this->m_Data[i];
}

void Queue::MakeEmpty()
{
	m_Head = 1;
	m_Tail = 0;
}

bool Queue::isEmpty()
{
	return (AddOne(m_Tail) == m_Head);
}

int* Queue::Front()
{
	if (isEmpty())
	{
		cout << "Error: Queue IS EMPTY :(" << endl;
		exit(1);
	}
	return (m_Data[m_Head]);
}

void Queue::EnQueue(int* item)
{
	if (AddOne(AddOne(m_Tail)) == m_Head)
	{
		cout << "Queue IS Full" << endl;
		exit(2);
	}
	m_Tail = AddOne(m_Tail);
	m_Data[m_Tail] = item;
}

int* Queue::DeQueue()
{
	int* item;

	if (isEmpty())
	{
		cout << "Error: Queue IS EMPTY" << endl;
		exit(3);
	}
	item = m_Data[m_Head];
	m_Head = AddOne(m_Head);
	return item;
}

int Queue::AddOne(int x)
{
	return ((1 + x) % MAX_SIZE);
}