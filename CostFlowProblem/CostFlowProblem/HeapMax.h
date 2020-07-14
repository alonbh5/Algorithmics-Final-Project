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

class Heap
{
private:
	PairOfData* m_Data;
	int m_MaxSize;                      //Max size of heap
	int m_HeapSize;                     //Current size of heap
	bool m_Allocated;                    //1 if heap allocated mamory

	static int Left(int i_NodeIdx);
	static int Right(int i_NodeIdx);
	static int Parent(int i_NodeIdx);
	void FixHeap(int i_NodeIdx);

public:
	Heap(int i_MaxSize);           //Turn arr[] into heap
	Heap(PairOfData* i_DataArr, int i_ArrSize);
	~Heap();
	bool IsEmpty();
	void makeEmpty(int i_MaxSize); //Allocate memory 
	PairOfData Max();
	PairOfData DeleteMax();
	void Insert(PairOfData i_Item);
	void Build (PairOfData* i_DataArr, int i_ArrSize);
	void IncreaseKey(int i_Place, int i_NewKey);
};

#endif // !_HEAPMAX_H