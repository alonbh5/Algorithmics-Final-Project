#ifndef _DIJKSTRA_H_
#define _DIJKSTRA_H_

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

public:
	Dijkstra(const int i_NumOfVertices);
	~Dijkstra();
	void RunDijkstra(AdjancencyMatrix& i_Graph, const int i_S);
	List* FindImprovePath(const int i_T);
	List* MinCutGroupS(const int i_S);
	List* MinCutGroupT(const int i_T);

private:
	void relax(const int i_U, const int i_V, const int i_S, AdjancencyMatrix& Graph, HeapMax& Q);
	void initialize(const int i_S);
};

#endif // !_DIJKSTRA_H_
