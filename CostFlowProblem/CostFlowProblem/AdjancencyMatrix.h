#ifndef _AdjancencyMatrix_H_
#define _AdjancencyMatrix_H_

#include "List.h"

struct EdgeInfo {
	int currentFlow ;
	int maxFlow;
	int residualFlow;
	bool isExist;
};

class AdjancencyMatrix
{
private:
	int m_NumOfVertex;
	EdgeInfo** m_Matrix;

public:
	AdjancencyMatrix(const int i_NumOfVertex);
	AdjancencyMatrix(const AdjancencyMatrix& i_Other);
	~AdjancencyMatrix();

	void MakeEmptyGraph();	
	void MakeGraphResidual(const AdjancencyMatrix& i_Other);

	EdgeInfo** GetMatrix() const;
	int GetNumOfVertex() const;
	List* GetAdjList(const int i_U) const;
	List* GetAdjListByResidual(const int i_U) const;

	bool IsAdjacent(const int i_U, const int i_V) const;
	void AddEdge(const int i_U, const int i_V, const int i_Weight);
	void RemoveEdge(const int i_U, const int i_V);
	void AddFlow(const List* i_Path, const int i_ResidualFlow);
	int MaxFlow(const int S) const;
};

#endif // !_AdjancencyMatrix_H_