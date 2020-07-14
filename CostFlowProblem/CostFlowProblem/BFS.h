#ifndef _BFS_H_
#define _BFS_H_
#pragma warning (disable:4996)

#include "Queue.h"
#include "AdjancencyMatrix.h"
#include "List.h"

class BFS
{
private:
	static const int Infinity = -1;
	int* m_Degree;
	int* m_Parent;
	int m_Size;
	void initialize(Queue& io_Q, int& io_S, int& io_U);

public:
	BFS(int i_NumOfVertices);
	//BFS(BFS& Other);
	~BFS();
	void createBFSTree(AdjancencyMatrix& i_Graph, int i_S);
	List* FindImprovePath(int i_T);
	List* MinCutGroupS(int i_S);
	List* MinCutGroupT(int i_T);
};

#endif // !_BFS_H_
