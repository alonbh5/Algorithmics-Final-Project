#ifndef _HEAPMAX_H_
#define _HEAPMAX_H_

#include <iostream>
using namespace std;

class HeapMax
{
private:
	const static int NOT_FOUND = -1;
	pair <int, int>* m_Data;
	int m_MaxSize;
	int m_HeapSize;
	bool m_Allocated;

public:
	HeapMax(const int i_MaxSize);
	~HeapMax();
	bool IsEmpty() const;	
	int Max() const;
	int DeleteMax();
	void Insert(const int i_Data, const int i_Key);
	void Build(const int* i_DataArr, const int i_ArrSize);
	void IncreaseKey(const int i_Place, const int i_NewKey);
	int FindPlaceOfKey(const int i_Key) const;

private:
	static int left(const int i_NodeIdx);
	static int right(const int i_NodeIdx);
	static int parent(const int i_NodeIdx);
	void fixHeap(const int i_NodeIdx);
	void createArrPairs(const int* i_DataArr, const int i_ArrSize);
	void makeEmpty(const int i_MaxSize);
};

#endif // !_HEAPMAX_H_