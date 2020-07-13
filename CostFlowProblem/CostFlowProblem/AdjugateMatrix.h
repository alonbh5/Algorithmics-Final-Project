#pragma once
class AdjugateMatrix
{
private:

	int m_NumOfVertex;
	int** m_MatrixWeight;
	int** m_MatrixAdj;

public:
	AdjugateMatrix(int i_NumOfVertex);
	~AdjugateMatrix();
	void MakeEmptyGraph(int i_n);
	bool IsAdjacent(int i_u, int i_v);
	//list GeAdjList(int i_u);
	void AddEdge(int i_u, int i_v, int i_c);
	void RemoveEdge(int i_u, int i_v);
};

