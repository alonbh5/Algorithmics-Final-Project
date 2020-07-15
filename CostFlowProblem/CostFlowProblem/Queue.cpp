#include "Queue.h"


Queue::Queue(int i_MaxSize)
{
	this->m_Data = new int[i_MaxSize];
	m_MaxSize = i_MaxSize;
	this->m_Head = 1;
	this->m_Tail = 0;
	for (int i = 0; i < i_MaxSize; i++)
	{
		this->m_Data[i] = 0;
	}
}

Queue::~Queue()
{
	delete[] (this->m_Data);
}

void Queue::MakeEmpty()
{
	m_Head = 1;
	m_Tail = 0;
}

bool Queue::IsEmpty()
{
	return (AddOne(m_Tail) == m_Head);
}

int Queue::Front()
{
	if (IsEmpty())
	{
		cout << "Error: Queue IS EMPTY :(" << endl;
		exit(1);
	}
	return (m_Data[m_Head]);
}

void Queue::EnQueue(const int i_Utem)
{
	if (AddOne(AddOne(m_Tail)) == m_Head)
	{
		cout << "Queue IS Full" << endl;
		exit(2);
	}
	m_Tail = AddOne(m_Tail);
	m_Data[m_Tail] = i_Utem;
}

int Queue::DeQueue()
{
	int item;

	if (IsEmpty())
	{
		cout << "Error: Queue IS EMPTY" << endl;
		exit(3);
	}
	item = m_Data[m_Head];
	m_Head = AddOne(m_Head);
	return item;
}

int Queue::AddOne(const int x)
{
	return ((1 + x) % m_MaxSize);
}