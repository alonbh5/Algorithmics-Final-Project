#include "AdjugateMatrix.h"



AdjugateMatrix::AdjugateMatrix(int i_NumOfVertex)
{
	m_NumOfVertex = i_NumOfVertex;
	m_Matrix = new int[i_NumOfVertex, i_NumOfVertex];
}


AdjugateMatrix::~AdjugateMatrix()
{
}
