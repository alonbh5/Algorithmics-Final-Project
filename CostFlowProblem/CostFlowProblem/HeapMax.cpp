#include "HeapMax.h"

HeapMax::HeapMax(int i_MaxSize)
{
	makeEmpty(i_MaxSize);
}

HeapMax::~HeapMax()
{
	if (m_Allocated)
		delete (this->m_Data);
	m_Data = nullptr;
}

void HeapMax::makeEmpty(const int i_MaxSize)
{
	m_Data = new pair<int, int>[i_MaxSize];
	m_MaxSize = i_MaxSize;
	m_HeapSize = 0;
	m_Allocated = true;
}

bool HeapMax::IsEmpty() const
{
	return (this->m_HeapSize == 0);
}

int HeapMax::Max() const
{
	return this->m_Data[0].second;
}

int HeapMax::parent(const int i_NodeIdx)
{
	return (i_NodeIdx - 1) / 2;
}

int HeapMax::left(const int i_NodeIdx) 
{
	return (2 * i_NodeIdx + 1);
}

int HeapMax::right(const int i_NodeIdx) 
{
	return (2 * i_NodeIdx + 2);
}

void HeapMax::fixHeap(const int i_NodeIdx)
{
	int max;
	int leftIndx = left(i_NodeIdx);
	int rightIndx = right(i_NodeIdx);

	if ((leftIndx < m_HeapSize) && (m_Data[leftIndx].first > m_Data[i_NodeIdx].first))
	{
		max = leftIndx;
	}
	else
	{
		max = i_NodeIdx;
	}
	if ((rightIndx < m_HeapSize) && (m_Data[rightIndx].first > m_Data[max].first))
	{
		max = rightIndx;
	}
	if (max != i_NodeIdx)
	{
		std::swap(m_Data[i_NodeIdx], m_Data[max]);
		fixHeap(max);
	}
}

int HeapMax::DeleteMax()
{
	if (m_HeapSize < 1)
	{
		cout << "Error: EMPTY HEAP\n";
		exit(1);
	}

	pair <int,int> max = m_Data[0];
	m_HeapSize--;
	m_Data[0] = m_Data[m_HeapSize];
	fixHeap(0);
	return (max.second);
}

void HeapMax::Insert(const int i_Data, const int i_Key)
{
	pair <int, int> newPair(i_Key, i_Data);

	if (m_HeapSize == m_MaxSize)
	{
		cout << "Error: HEAP FULL\n";
		exit(1);
	}

	int i = m_HeapSize;
	m_HeapSize++;

	while ((i > 0) && (m_Data[parent(i)].first < newPair.first))
	{
		m_Data[i] = m_Data[parent(i)];
		i = parent(i);
	}
	m_Data[i] = newPair;
}

void HeapMax::Build(const int* i_DataArr, const int i_ArrSize)
{	
	createArrPairs(i_DataArr, i_ArrSize);
	m_HeapSize = m_MaxSize = i_ArrSize;		             
	for (int i = (i_ArrSize / 2) - 1; i >= 0; i--)
		fixHeap(i);
}

void HeapMax::createArrPairs(const int* i_DataArr, const int i_ArrSize)
{
	for (int i = 0; i < i_ArrSize; i++)
	{
		m_Data[i].second = i; //vertex
		m_Data[i].first = i_DataArr[i]; //weight
	}
}

void HeapMax::IncreaseKey(const int i_Place, const int i_NewKey)
{	
	pair<int,int> temp;
	int i = i_Place;
	m_Data[i].first = i_NewKey;
	temp = m_Data[i];
	std::swap(m_Data[i], m_Data[m_HeapSize]);	
	while ((i > 0) && (m_Data[parent(i)].first < temp.first))
	{
		m_Data[i] = m_Data[parent(i)];
		i = parent(i);
	}
	m_Data[i] = temp;
}

int HeapMax::FindPlaceOfKey(const int i_Data) const
{
	for (int i = 0; i < m_HeapSize; i++)
	{
		if (m_Data[i].second == i_Data)
		{
			return i;
		}
	}
	return NOT_FOUND;
}
