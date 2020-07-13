#pragma once

#include "List.h"
struct EdgeInfo {
	int currentFlow;
	int maxFlow;
	int ResidualFlow;
	bool isExist;
};
class AdjugateMatrix
{
public:

	int m_NumOfVertex;
	EdgeInfo** m_Matrix;

public:
	AdjugateMatrix(int i_NumOfVertex);
	AdjugateMatrix(AdjugateMatrix& Other);
	~AdjugateMatrix();
	void MakeEmptyGraph();
	bool IsAdjacent(int i_u, int i_v);
	List GetAdjList(int i_u);
	List GetAdjListByResidual(int i_u);
	void AddEdge(int i_u, int i_v, int i_c);
	void RemoveEdge(int i_u, int i_v);
	void InitFlow();
	void PrintEdges();
	void MakeGraphResidual(AdjugateMatrix& Other);
	void CopyOnlyFlowEdges(AdjugateMatrix& Other);
	void AddFlow(List Path, int ResidualFlow);

};

