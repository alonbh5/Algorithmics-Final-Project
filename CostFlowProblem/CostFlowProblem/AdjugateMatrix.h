#pragma once

#include "List.h"

class AdjugateMatrix
{
public:

	int m_NumOfVertex;
	int** m_MatrixWeight;
	int** m_MatrixAdj;

public:
	AdjugateMatrix(int i_NumOfVertex);
	AdjugateMatrix(AdjugateMatrix& Other);
	~AdjugateMatrix();
	void MakeEmptyGraph();
	bool IsAdjacent(int i_u, int i_v);
	List GetAdjList(int i_u);
	void AddEdge(int i_u, int i_v, int i_c);
	void RemoveEdge(int i_u, int i_v);
	void InitFlow();

};

