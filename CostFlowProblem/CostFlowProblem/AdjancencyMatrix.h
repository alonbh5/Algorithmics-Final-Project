#ifndef _AdjancencyMatrix_H_
#define _AdjancencyMatrix_H_
#pragma warning (disable:4996) 

#include "List.h"
struct EdgeInfo {
	int currentFlow;
	int maxFlow;
	int ResidualFlow;
	bool isExist;
};
class AdjancencyMatrix
{
public: // make it private
	int m_NumOfVertex;
	EdgeInfo** m_Matrix;

public:
	AdjancencyMatrix(int i_NumOfVertex);
	AdjancencyMatrix(AdjancencyMatrix& i_Other);
	~AdjancencyMatrix();
	void MakeEmptyGraph();
	bool IsAdjacent(int i_U, int i_V);
	List* GetAdjList(int i_U);
	List* GetAdjListByResidual(int i_U);
	void AddEdge(int i_U, int i_V, int i_Weight);
	void RemoveEdge(int i_U, int i_V);
	void InitFlow();
	void PrintEdges();
	void MakeGraphResidual(AdjancencyMatrix& i_Other);
	void CopyOnlyFlowEdges(AdjancencyMatrix& i_Other);
	void AddFlow(List* i_Path, int i_ResidualFlow);
	int MaxFlow(int S);
};

#endif // !_AdjancencyMatrix_H_