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
	static int Left(int IndexOfNode);
	static int Right(int IndexOfNode);
	static int Parent(int IndexOfNode);
	void FixHeap(int IndexOfNode);
public:
	Heap(int MaxSize);           //Turn arr[] into heap
	~Heap();
	bool IsEmpty();
	void makeEmpty(int MaxSize); //Allocate memory 
	PairOfData Max();
	PairOfData DeleteMax();
	void Insert(PairOfData item);
};

#endif // !_HEAPMAX_H