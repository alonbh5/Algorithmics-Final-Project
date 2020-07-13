#include "AdjugateMatrix.h"

AdjugateMatrix::AdjugateMatrix(int i_NumOfVertex)
{
	m_NumOfVertex = i_NumOfVertex;
	m_MatrixAdj = new int*[i_NumOfVertex];
	m_MatrixWeight = new int*[i_NumOfVertex];
	for (int i = 0; i < i_NumOfVertex; i++)
	{
		m_MatrixAdj[i] = new int[i_NumOfVertex];
		m_MatrixWeight[i] = new int[i_NumOfVertex];
	}

}

AdjugateMatrix::~AdjugateMatrix()
{
	delete[] m_MatrixAdj;
	delete[] m_MatrixWeight;
}

void AdjugateMatrix::MakeEmptyGraph(int i_n)
{
	for (int i = 0; i < m_NumOfVertex; i++)
	{
		for (int j = 0; i < m_NumOfVertex; i++)
		{
			m_MatrixWeight[i][j] = 0;
			m_MatrixAdj[i][j] = 0;
		}
	}
}

bool AdjugateMatrix::IsAdjacent(int i_u, int i_v)
{
	if (m_MatrixAdj[i_u][i_v] == 1)
	{
		return true;
	}
	return false;
}

void AdjugateMatrix::AddEdge(int i_u, int i_v, int i_c)
{
	if (m_MatrixAdj[i_u][i_v] == 0)
	{
		m_MatrixAdj[i_u][i_v] = 1;
		m_MatrixWeight[i_u][i_v] = i_c;
	}
}

void AdjugateMatrix::RemoveEdge(int i_u, int i_v)
{
	m_MatrixAdj[i_u][i_v] = 0;
	m_MatrixWeight[i_u][i_v] = 0;
}

