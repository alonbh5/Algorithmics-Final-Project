#include "HeapMax.h"


//C'tor: allocate memory for the heap and make the heap empty.
HeapMax::HeapMax(int i_MaxSize)
{
	//makeEmpty(i_MaxSize);
	m_MaxSize = i_MaxSize;
	m_Data = new PairOfData[i_MaxSize];
	m_HeapSize = 0;
	m_Allocated = true;
}

//D'tor: delete memory only if allocates by heap
HeapMax::~HeapMax()
{
	//if (m_Allocated)
	//	delete (this->m_Data);
	m_Data = nullptr;
}


void HeapMax::makeEmpty(const int i_MaxSize)
{
	m_Data = new PairOfData[i_MaxSize];
	m_MaxSize = i_MaxSize;
	m_HeapSize = 0;
	m_Allocated = true;
}

bool HeapMax::IsEmpty()
{
	return (this->m_HeapSize == 0);
}

int HeapMax::Max()
{
	return this->m_Data[0].data;
}

//Private Member functions of Heap class

int HeapMax::Parent(const int i_NodeIdx)
{
	return (i_NodeIdx - 1) / 2;
}

int HeapMax::Left(const int i_NodeIdx)
{
	return (2 * i_NodeIdx + 1);
}

int HeapMax::Right(const int i_NodeIdx) 
{
	return (2 * i_NodeIdx + 2);
}

void HeapMax::FixHeap(const int i_NodeIdx)    //Fixes the heap that has node as root
{
	int max;
	int left = Left(i_NodeIdx);
	int right = Right(i_NodeIdx);

	//Find min among node, left and right.	
	if ((left < m_HeapSize) && (m_Data[left].key > m_Data[i_NodeIdx].key))
		max = left;
	else
		max = i_NodeIdx;
	if ((right < m_HeapSize) && (m_Data[right].key > m_Data[max].key))
		max = right;

	//Seap values if neccessary, and continue fixing the heap towards the leaves.
	if (max != i_NodeIdx)
	{
		std::swap(m_Data[i_NodeIdx], m_Data[max]);
		FixHeap(max);
	}
}

//Delete Maximum which is found in the root of heap, and fix heap.
int HeapMax::DeleteMax()
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
	return (max.data);
}

//Add a new leaf for item, and swap upwards until item is in its correct position.
void HeapMax::Insert(const PairOfData i_Item)
{
	if (m_HeapSize == m_MaxSize)
	{
		cout << "Error: HEAP FULL\n";
		exit(1);
	}

	int i = m_HeapSize;
	m_HeapSize++;

	while ((i > 0) && (m_Data[Parent(i)].key < i_Item.key))
	{
		m_Data[i] = m_Data[Parent(i)];
		i = Parent(i);
	}
	m_Data[i] = i_Item;
}

//C'tor: convert an array which contains n numbers into a heap.
//Idea: the numbers in places n-1,...,n/2 are leaves.
//Build small heaps starting from leaves, and fix heaps while going towards the root.


void HeapMax::Build(int* i_DataArr, const int i_ArrSize)
{	
	createArrPairs(i_DataArr, i_ArrSize);
	m_HeapSize = m_MaxSize = i_ArrSize;		             

	for (int i = (i_ArrSize / 2) - 1; i >= 0; i--) //flyde
		FixHeap(i);
}

void HeapMax::createArrPairs(int* i_DataArr, const int i_ArrSize)
{
	
	for (int i = 0; i < i_ArrSize; i++)
	{
		m_Data[i].data = i; //vertex
		m_Data[i].key = i_DataArr[i]; //witgh
	}
	
}

void HeapMax::IncreaseKey(const int i_Place, const int i_NewKey)
{
	
	PairOfData temp;
	int i = i_Place;
	
	m_Data[i].key = i_NewKey;
	temp = m_Data[i];
	std::swap(m_Data[i], m_Data[m_HeapSize]);	

	while ((i > 0) && (m_Data[Parent(i)].key < temp.key))
	{
		m_Data[i] = m_Data[Parent(i)];
		i = Parent(i);
	}
	m_Data[i] = temp;

}

int HeapMax::findPlaceOfKey(const int i_Data) const
{
	for (int i = 0; i < m_HeapSize; i++)
	{
		if (m_Data[i].data == i_Data)
		{
			return i;
		}
	}
	return -1;
}
