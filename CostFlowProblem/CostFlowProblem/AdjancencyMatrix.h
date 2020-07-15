#ifndef _AdjancencyMatrix_H_
#define _AdjancencyMatrix_H_
#pragma warning (disable:4996) 

#include "List.h"
struct EdgeInfo {
	int currentFlow;
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
	AdjancencyMatrix(AdjancencyMatrix&& i_Other);
	~AdjancencyMatrix();
	EdgeInfo** GetMatrix() const;
	int GetNumOfVertex() const;
	List* GetAdjList(const int i_U) const;
	List* GetAdjListByResidual(const int i_U) const;
	void MakeEmptyGraph();
	void AddEdge(const int i_U, const int i_V, const int i_Weight);
	void RemoveEdge(const int i_U, const int i_V);
	void InitFlow();
	void MakeGraphResidual(const AdjancencyMatrix& i_Other);
	void AddFlow(const List* i_Path, const int i_ResidualFlow);
	int MaxFlow(const int S) const;
	bool IsAdjacent(const int i_U, const int i_V) const;
};

#endif // !_AdjancencyMatrix_H_