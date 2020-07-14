#ifndef _DIJKSTRA_H
#define _DIJKSTRA_H
#pragma warning (disable:4996)

#include "HeapMax.h"
#include "AdjancencyMatrix.h"
#include "List.h"

class Dijkstra
{
private:
	static const int Infinity = -1;
	int* m_Degree;
	int* m_Parent;
	int m_Size;
	void initialize(int& i_S);

public:
	Dijkstra(int i_NumOfVertices);
	~Dijkstra();
	void createDijkstraTree(AdjancencyMatrix& i_Graph, int i_S);
	void relax(int i_U, int i_V, int i_S, AdjancencyMatrix& Graph, HeapMax& Q);
	List* FindImprovePath(int i_T);
	List* MinCutGroupS(int i_S);
	List* MinCutGroupT(int i_T);
};

#endif // !_DIJKSTRA_H_
