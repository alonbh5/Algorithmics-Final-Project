#ifndef _HEAPMAX_H
#define _HEAPMAX_H

#pragma warning (disable:4996)
#include <iostream>
using namespace std;

struct PairOfData
{
	int data; //vertex
	int key; //weight
};

class HeapMax
{
private:
	PairOfData* m_Data;
	int m_MaxSize;                      //Max size of heap
	int m_HeapSize;                     //Current size of heap
	bool m_Allocated;                    //1 if heap allocated mamory

	static int Left(const int i_NodeIdx);
	static int Right(const int i_NodeIdx);
	static int Parent(const int i_NodeIdx);
	void FixHeap(const int i_NodeIdx);

public:
	HeapMax(const int i_MaxSize);           //Turn arr[] into heap
	HeapMax() = default;
	~HeapMax();
	bool IsEmpty();
	void makeEmpty(const int i_MaxSize); //Allocate memory 
	int Max();
	int DeleteMax();
	void Insert(const PairOfData i_Item);
	void Build(int* i_DataArr, const int i_ArrSize);
	void IncreaseKey(const int i_Place, const int i_NewKey);
	int findPlaceOfKey(const int i_Key) const;
	void createArrPairs(int* i_DataArr, const int i_ArrSize);
};

#endif // !_HEAPMAX_H