#include "HeapMax.h"


//C'tor: allocate memory for the heap and make the heap empty.
void Heap::makeEmpty(int MaxSize)
{	
	m_Data = new PairOfData[MaxSize];
	m_MaxSize = MaxSize;
	m_HeapSize = 0;
	m_Allocated = true;
}

//D'tor: delete memory only if allocates by heap
Heap::~Heap()
{
	if (m_Allocated)
		delete[] m_Data;
	m_Data = nullptr;
}

bool Heap::IsEmpty()
{
	return (this->m_HeapSize == 0);
}

PairOfData Heap::Max()
{
	return this->m_Data[0];
}

//Private Member functions of Heap class

int Heap::Parent(int IndexOfNode)
{
	return (IndexOfNode - 1) / 2;
}

int Heap::Left(int IndexOfNode)
{
	return (2 * IndexOfNode + 1);
}

int Heap::Right(int IndexOfNode)
{
	return (2 * IndexOfNode + 2);
}

void Heap::FixHeap(int IndexOfNode)    //Fixes the heap that has node as root
{
	int max;
	int left = Left(IndexOfNode);
	int right = Right(IndexOfNode);

	//Find min among node, left and right.	
	if ((left < m_HeapSize) && (m_Data[left].key > m_Data[IndexOfNode].key))
		max = left;
	else
		max = IndexOfNode;
	if ((right < m_HeapSize) && (m_Data[right].key > m_Data[max].key))
		max = right;

	//Seap values if neccessary, and continue fixing the heap towards the leaves.
	if (max != IndexOfNode)
	{
		std::swap(m_Data[IndexOfNode], m_Data[max]);
		FixHeap(max);
	}
}

//Delete Maximum which is found in the root of heap, and fix heap.
PairOfData Heap::DeleteMax()
{
	if (m_HeapSize < 1)
	{
		cout << "Error: EMPTY HEAP\n";
		exit(1);
	}

	PairOfData max = m_Data[0];
	m_HeapSize--;
	m_Data[0] = m_Data[m_HeapSize];
	FixHeap(0);
	return (max);
}

//Add a new leaf for item, and swap upwards until item is in its correct position.
void Heap::Insert(PairOfData item)
{
	if (m_HeapSize == m_MaxSize)
	{
		cout << "Error: HEAP FULL\n";
		exit(1);
	}

	int i = m_HeapSize;
	m_HeapSize++;

	while ((i > 0) && (m_Data[Parent(i)].key < item.key))
	{
		m_Data[i] = m_Data[Parent(i)];
		i = Parent(i);
	}
	m_Data[i] = item;
}

//C'tor: convert an array which contains n numbers into a heap.
//Idea: the numbers in places n-1,...,n/2 are leaves.
//Build small heaps starting from leaves, and fix heaps while going towards the root.
Heap::Heap(Person A[], int n)
{
	heapSize = maxSize = n;
	int x = 0;
	data = A;                   //Assign array A to data pointer
	allocated = 0;              //Memory not allocated by heap

	for (int i = (n / 2) - 1; i >= 0; i--) //flyde
		FixHeap(i, x);
}