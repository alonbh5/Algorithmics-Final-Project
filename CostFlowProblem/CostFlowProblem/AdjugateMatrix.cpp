#include "AdjugateMatrix.h"

AdjugateMatrix::AdjugateMatrix(int i_NumOfVertex)
{
	m_NumOfVertex = i_NumOfVertex;
	m_Matrix = new EdgeInfo*[i_NumOfVertex];
	for (int i = 0; i < i_NumOfVertex; i++)
	{
		m_Matrix[i] = new EdgeInfo[i_NumOfVertex];
	}

	MakeEmptyGraph();
}

AdjugateMatrix::AdjugateMatrix(AdjugateMatrix& Other)
{
	this->m_NumOfVertex = Other.m_NumOfVertex;
	this->m_Matrix = new EdgeInfo*[this->m_NumOfVertex];
	for (int i = 0; i < this->m_NumOfVertex; i++)
	{
		this->m_Matrix[i] = new EdgeInfo[this->m_NumOfVertex];
		for (int j = 0; j < this->m_NumOfVertex; j++)
		{
			this->m_Matrix[i][j] = Other.m_Matrix[i][j];
		}
	}
}

AdjugateMatrix::~AdjugateMatrix()
{
	delete[] m_Matrix;
}

void AdjugateMatrix::MakeEmptyGraph()
{
	for (int i = 0; i < m_NumOfVertex; i++)
	{
		for (int j = 0; j < m_NumOfVertex; j++)
		{
			this->m_Matrix[i][j].currentFlow = 0;
			this->m_Matrix[i][j].ResidualFlow = 0;
			this->m_Matrix[i][j].maxFlow = 0;
			this->m_Matrix[i][j].isExist = false;
		}
	}
}

bool AdjugateMatrix::IsAdjacent(int i_u, int i_v)
{
	return (m_Matrix[i_u][i_v].isExist);
}

void AdjugateMatrix::AddEdge(int i_u, int i_v, int i_c)
{
	if (!m_Matrix[i_u][i_v].isExist)
	{
		m_Matrix[i_u][i_v].isExist = true;
		m_Matrix[i_u][i_v].currentFlow = 0;
		m_Matrix[i_u][i_v].maxFlow = i_c;
		m_Matrix[i_u][i_v].ResidualFlow = i_c;
	}
}

void AdjugateMatrix::RemoveEdge(int i_u, int i_v)
{
	m_Matrix[i_u][i_v].isExist = false;
}

void AdjugateMatrix::InitFlow()
{
	for (int i = 0; i < m_NumOfVertex; i++)
	{
		for (int j = 0; j < m_NumOfVertex; j++)
		{
			if(m_Matrix[i][j].isExist)
				m_Matrix[i][j].currentFlow = 0;
		}
	}
}

void AdjugateMatrix::PrintEdges()
{
	for (int i = 0; i < this->m_NumOfVertex; i++)
	{
		for (int j = 0; j < this->m_NumOfVertex; j++)
		{
			if (this->m_Matrix[i][j].isExist)
			{
				std::cout << "edge " << i+1 << " " << j+1 << " cur flow " << m_Matrix[i][j].currentFlow << " max flow " << m_Matrix[i][j].maxFlow << " res " << m_Matrix[i][j].ResidualFlow<<std::endl;
			}
		}
		
	}
}

void AdjugateMatrix::MakeGraphResidual(AdjugateMatrix& Other)
{
	this->m_NumOfVertex = Other.m_NumOfVertex;	
	for (int i = 0; i < this->m_NumOfVertex; i++)
	{		
		for (int j = 0; j < this->m_NumOfVertex; j++)
		{
			if (Other.m_Matrix[i][j].maxFlow != 0)
			{
				this->m_Matrix[i][j] = Other.m_Matrix[i][j];
			}
			else
			{
				//this->m_Matrix[i][j].isExist = false;
			}
		}
	}

	for (int i = 0; i < this->m_NumOfVertex; i++)
	{
		for (int j = 0; j < this->m_NumOfVertex; j++)
		{
			if (this->m_Matrix[i][j].isExist && !this->m_Matrix[j][i].isExist)
			{
				//anti mkbila
				this->m_Matrix[j][i].isExist = true;				
				this->m_Matrix[j][i].currentFlow = this->m_Matrix[i][j].maxFlow * -1;
				this->m_Matrix[j][i].maxFlow = 0;
				this->m_Matrix[j][i].ResidualFlow = this->m_Matrix[j][i].maxFlow - this->m_Matrix[j][i].currentFlow;
			}
		}
	}

}

void AdjugateMatrix::CopyOnlyFlowEdges(AdjugateMatrix& Other)
{
	for (int i = 0; i < this->m_NumOfVertex; i++)
	{
		for (int j = 0; j < this->m_NumOfVertex; j++)
		{
			if (Other.m_Matrix[i][j].currentFlow > 0)
			{
				this->m_Matrix[i][j] = Other.m_Matrix[i][j];
			}
		}
	}
}

void AdjugateMatrix::AddFlow(List Path, int i_ResidualFlow)
{
	int u, v;
	Node* currentNode = Path.Head;
	while (currentNode->next != nullptr)
	{
		u = currentNode->data;
		v = currentNode->next->data;
		m_Matrix[u][v].currentFlow += i_ResidualFlow;
		m_Matrix[u][v].ResidualFlow = m_Matrix[u][v].maxFlow - m_Matrix[u][v].currentFlow;

		//anti makbila
		m_Matrix[v][u].currentFlow = m_Matrix[u][v].currentFlow * -1;
		m_Matrix[v][u].ResidualFlow = m_Matrix[v][u].maxFlow - m_Matrix[v][u].currentFlow;
		//m_Matrix[v][u].isExist = true;


		currentNode = currentNode->next;
	}
}


List AdjugateMatrix::GetAdjList(int i_u)
{
	List AdjList;
	for (int i = 0; i < m_NumOfVertex; i++)
	{
		if (m_Matrix[i_u][i].isExist)
		{
			AdjList.InsertToTail(i);
		}
	}

	return AdjList;
}

List AdjugateMatrix::GetAdjListByResidual(int i_u)
{
	List AdjList;
	for (int i = 0; i < m_NumOfVertex; i++)
	{
		if (m_Matrix[i_u][i].isExist && m_Matrix[i_u][i].ResidualFlow != 0 && m_Matrix[i_u][i].maxFlow !=0)
		{
			AdjList.InsertToTail(i);
		}
	}

	return AdjList;
}

