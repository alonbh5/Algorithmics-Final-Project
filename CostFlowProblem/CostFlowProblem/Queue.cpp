#include "Queue.h"

Queue::Queue()
{	
	m_Head = new Node(DUMMY);
	m_Tail = m_Head;
}

Queue::~Queue()
{
	MakeEmpty();
	delete m_Head;
}

void Queue::MakeEmpty()
{
	if (!IsEmpty())
	{
		Node* curNode = m_Head->GetNext();
		Node* temp = nullptr;

		while (curNode != nullptr)
		{
			temp = curNode->GetNext();
			delete curNode;
			curNode = temp;
		}
		m_Tail = m_Head;
	}

}

bool Queue::IsEmpty() const
{
	return (m_Tail == m_Head);
}

int Queue::Front() const
{
	if (IsEmpty())
	{
		cout << "Error: Queue IS EMPTY :(" << endl;
		exit(1);
	}
	return (m_Head->GetNext()->GetData());
}

void Queue::EnQueue(const int i_Utem)
{
	Node* newnode = new Node(i_Utem);
	m_Tail->InsertAfter(newnode);
	m_Tail = newnode;
}

int Queue::DeQueue()
{
	if (IsEmpty())
	{
		cout << "Error: Queue IS EMPTY :(" << endl;
		exit(1);
	}

	Node* temp = m_Head->DeleteAfter();
	int item = temp->GetData();
	if (m_Tail == temp)
	{
		m_Tail = m_Head;
	}

	delete temp;
	return item;
}

