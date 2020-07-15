#ifndef _BFS_H_
#define _BFS_H_

#include "Queue.h"
#include "AdjancencyMatrix.h"
#include "List.h"

class BFS
{
private:
	const int Infinity = -1;
	int* m_Degree;
	int* m_Parent;
	int m_Size;
	void initialize(Queue& io_Q, const int io_S, int& io_U);

public:
	BFS(const int i_NumOfVertices);
	~BFS();
	void createBFSTree(AdjancencyMatrix& i_Graph, const int i_S);
	List* FindImprovePath(const int i_T);
	List* MinCutGroupS(const int i_S);
	List* MinCutGroupT(const int i_T);
};

#endif // !_BFS_H_
