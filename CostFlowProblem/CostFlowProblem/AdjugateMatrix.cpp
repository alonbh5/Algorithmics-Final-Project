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

	MakeEmptyGraph();

}

AdjugateMatrix::AdjugateMatrix(AdjugateMatrix& Other)
{
	this->m_NumOfVertex = Other.m_NumOfVertex;
	this->m_MatrixWeight = new int*[this->m_NumOfVertex];
	this->m_MatrixAdj = new int*[this->m_NumOfVertex];
	for (int i = 0; i < this->m_NumOfVertex; i++)
	{
		this->m_MatrixWeight[i] = new int[this->m_NumOfVertex];
		this->m_MatrixAdj[i] = new int[this->m_NumOfVertex];
		for (int j = 0; j < this->m_NumOfVertex; j++)
		{
			this->m_MatrixAdj[i][j] = Other.m_MatrixAdj[i][j];
			this->m_MatrixWeight[i][j] = Other.m_MatrixWeight[i][j];
		}
	}
}

AdjugateMatrix::~AdjugateMatrix()
{
	delete[] m_MatrixAdj;
	delete[] m_MatrixWeight;
}

void AdjugateMatrix::MakeEmptyGraph()
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

void AdjugateMatrix::InitFlow()
{
	for (int i = 0; i < m_NumOfVertex; i++)
	{
		for (int j = 0; j < m_NumOfVertex; j++)
		{
			m_MatrixWeight[i][j] = 0;
		}
	}
}


List AdjugateMatrix::GetAdjList(int i_u)
{
	List AdjList;
	for (int i = 0; i < m_NumOfVertex; i++)
	{
		if (m_MatrixAdj[i_u][i] == 1)
		{
			AdjList.InsertToTail(i);
		}
	}

	return AdjList;
}

