#include "AdjancencyMatrix.h"

AdjancencyMatrix::AdjancencyMatrix(int i_NumOfVertex)
{
	m_NumOfVertex = i_NumOfVertex;
	m_Matrix = new EdgeInfo*[i_NumOfVertex];
	for (int i = 0; i < i_NumOfVertex; i++)
	{
		m_Matrix[i] = new EdgeInfo[i_NumOfVertex];
	}

	MakeEmptyGraph();
}

AdjancencyMatrix::AdjancencyMatrix(AdjancencyMatrix& i_Other)
{
	this->m_NumOfVertex = i_Other.m_NumOfVertex;
	this->m_Matrix = new EdgeInfo*[this->m_NumOfVertex];
	for (int i = 0; i < this->m_NumOfVertex; i++)
	{
		this->m_Matrix[i] = new EdgeInfo[this->m_NumOfVertex];
		for (int j = 0; j < this->m_NumOfVertex; j++)
		{
			this->m_Matrix[i][j] = i_Other.m_Matrix[i][j];
		}
	}
}

AdjancencyMatrix::AdjancencyMatrix(AdjancencyMatrix&& i_Other)
{
	this->m_Matrix = i_Other.m_Matrix;
	this->m_NumOfVertex = i_Other.m_NumOfVertex;
}

AdjancencyMatrix::~AdjancencyMatrix()
{
	for (int i = 0; i < m_NumOfVertex; i++)
	{
		delete[] this->m_Matrix[i];
	}
	delete[] m_Matrix;
}

void AdjancencyMatrix::MakeEmptyGraph()
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

bool AdjancencyMatrix::IsAdjacent(int i_U, int i_V)
{
	return (m_Matrix[i_U][i_V].isExist);
}

void AdjancencyMatrix::AddEdge(int i_U, int i_V, int i_Weight)
{
	if (!m_Matrix[i_U][i_V].isExist)
	{
		m_Matrix[i_U][i_V].isExist = true;
		m_Matrix[i_U][i_V].currentFlow = 0;
		m_Matrix[i_U][i_V].maxFlow = i_Weight;
		m_Matrix[i_U][i_V].ResidualFlow = i_Weight;
	}
}

void AdjancencyMatrix::RemoveEdge(int i_U, int i_V)
{
	m_Matrix[i_U][i_V].isExist = false;
}

void AdjancencyMatrix::InitFlow()
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

void AdjancencyMatrix::PrintEdges()
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

void AdjancencyMatrix::MakeGraphResidual(AdjancencyMatrix& i_Other)
{
	this->m_NumOfVertex = i_Other.m_NumOfVertex;	
	for (int i = 0; i < this->m_NumOfVertex; i++)
	{		
		for (int j = 0; j < this->m_NumOfVertex; j++)
		{
			if (i_Other.m_Matrix[i][j].maxFlow != 0)
			{
				this->m_Matrix[i][j] = i_Other.m_Matrix[i][j];
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
void AdjancencyMatrix::CopyOnlyFlowEdges(AdjancencyMatrix& i_Other)
{
	for (int i = 0; i < this->m_NumOfVertex; i++)
	{
		for (int j = 0; j < this->m_NumOfVertex; j++)
		{
			if (i_Other.m_Matrix[i][j].currentFlow > 0)
			{
				this->m_Matrix[i][j] = i_Other.m_Matrix[i][j];
			}
		}
	}
}

void AdjancencyMatrix::AddFlow(List* i_Path, int i_ResidualFlow)
{
	int u, v;
	Node* currentNode = i_Path->GetHead();
	while (currentNode->GetNext() != nullptr)
	{
		u = currentNode->GetData();
		v = currentNode->GetNext()->GetData();
		m_Matrix[u][v].currentFlow += i_ResidualFlow;
		m_Matrix[u][v].ResidualFlow = m_Matrix[u][v].maxFlow - m_Matrix[u][v].currentFlow;

		//anti makbila
		m_Matrix[v][u].currentFlow = m_Matrix[u][v].currentFlow * -1;
		m_Matrix[v][u].ResidualFlow = m_Matrix[v][u].maxFlow - m_Matrix[v][u].currentFlow;
		//m_Matrix[v][u].isExist = true;


		currentNode = currentNode->GetNext();
	}
}

int AdjancencyMatrix::MaxFlow(int S)
{
	int maxFlow = 0;
	List* adjList = GetAdjList(S);
	Node* currNode = adjList->GetHead();
	while (currNode)
	{
		maxFlow += m_Matrix[S][currNode->GetData()].currentFlow;
		currNode = currNode->GetNext();
	}
	return maxFlow;
	delete adjList;
}


List* AdjancencyMatrix::GetAdjList(int i_U)
{
	List* AdjList = new List();
	for (int i = 0; i < m_NumOfVertex; i++)
	{
		if (m_Matrix[i_U][i].isExist)
		{
			AdjList->InsertToTail(i);
		}
	}

	return AdjList;
}

List* AdjancencyMatrix::GetAdjListByResidual(int i_U)
{
	List* AdjList = new List();
	for (int i = 0; i < m_NumOfVertex; i++)
	{
		if (m_Matrix[i_U][i].isExist && m_Matrix[i_U][i].ResidualFlow != 0 && m_Matrix[i_U][i].maxFlow !=0)
		{
			AdjList->InsertToTail(i);
		}
	}

	return AdjList;
}

