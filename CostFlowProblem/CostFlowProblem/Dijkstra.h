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
	void initialize(const int i_S);

public:
	Dijkstra(const int i_NumOfVertices);
	~Dijkstra();
	void createDijkstraTree(AdjancencyMatrix& i_Graph, const int i_S);
	void relax(const int i_U, const int i_V, const int i_S, AdjancencyMatrix& Graph, HeapMax& Q);
	List* FindImprovePath(const int i_T);
	List* MinCutGroupS(const int i_S);
	List* MinCutGroupT(const int i_T);
};

#endif // !_DIJKSTRA_H_
