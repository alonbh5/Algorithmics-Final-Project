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

public:
	BFS(const int i_NumOfVertices);
	~BFS();
	void RunBFS(AdjancencyMatrix& i_Graph, const int i_S);
	List* FindImprovePath(const int i_T) const;
	List* MinCutGroupS(const int i_S) const;
	List* MinCutGroupT(const int i_T) const;

private:
	void initialize(Queue& io_Q, const int io_S, int& io_U);
};

#endif // !_BFS_H_
