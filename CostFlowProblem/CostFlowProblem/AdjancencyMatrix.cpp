#include "AdjancencyMatrix.h"

AdjancencyMatrix::AdjancencyMatrix(const int i_NumOfVertex)
{
	m_NumOfVertex = i_NumOfVertex;
	m_Matrix = new EdgeInfo*[i_NumOfVertex];
	for (int i = 0; i < i_NumOfVertex; i++)
	{
		m_Matrix[i] = new EdgeInfo[i_NumOfVertex];
	}
	MakeEmptyGraph();
}

AdjancencyMatrix::AdjancencyMatrix(const AdjancencyMatrix& i_Other)
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


AdjancencyMatrix::~AdjancencyMatrix()
{
	if (m_Matrix != nullptr)
	{
		for (int i = 0; i < m_NumOfVertex; i++)
		{
			delete[] this->m_Matrix[i];
		}
		delete[] m_Matrix;
	}
}

EdgeInfo** AdjancencyMatrix::GetMatrix() const
{
	return m_Matrix;
}

int AdjancencyMatrix::GetNumOfVertex() const
{
	return m_NumOfVertex;
}

void AdjancencyMatrix::MakeEmptyGraph()
{
	for (int i = 0; i < m_NumOfVertex; i++)
	{
		for (int j = 0; j < m_NumOfVertex; j++)
		{
			this->m_Matrix[i][j].currentFlow = 0;
			this->m_Matrix[i][j].residualFlow = 0;
			this->m_Matrix[i][j].maxFlow = 0;
			this->m_Matrix[i][j].isExist = false;
		}
	}
}

bool AdjancencyMatrix::IsAdjacent(const int i_U, const int i_V) const
{
	return (m_Matrix[i_U][i_V].isExist);
}

void AdjancencyMatrix::AddEdge(const int i_U, const int i_V, const int i_Weight)
{
	if (!m_Matrix[i_U][i_V].isExist)
	{
		m_Matrix[i_U][i_V].isExist = true;
		m_Matrix[i_U][i_V].currentFlow = 0;
		m_Matrix[i_U][i_V].maxFlow = i_Weight;
		m_Matrix[i_U][i_V].residualFlow = i_Weight;
	}
}

void AdjancencyMatrix::RemoveEdge(const int i_U, const int i_V)
{
	m_Matrix[i_U][i_V].isExist = false;
}


void AdjancencyMatrix::MakeGraphResidual(const AdjancencyMatrix& io_Other)
{
	copyOnlyPostiveMaxFlowEdges(io_Other);
	addAntiEdges();
}

void AdjancencyMatrix::AddFlow(const List* i_Path, const int i_ResidualFlow)
{
	int u, v;
	Node* currentNode = i_Path->GetHead();
	while (currentNode->GetNext() != nullptr)
	{
		u = currentNode->GetData();
		v = currentNode->GetNext()->GetData();
		m_Matrix[u][v].currentFlow += i_ResidualFlow;
		m_Matrix[u][v].residualFlow = m_Matrix[u][v].maxFlow - m_Matrix[u][v].currentFlow;

		//anti makbila
		m_Matrix[v][u].currentFlow = m_Matrix[u][v].currentFlow * -1;
		m_Matrix[v][u].residualFlow = m_Matrix[v][u].maxFlow - m_Matrix[v][u].currentFlow;
		m_Matrix[v][u].isExist = true;


		currentNode = currentNode->GetNext();
	}
}

int AdjancencyMatrix::MaxFlow(const int S) const
{
	int maxFlow = 0;
	List* adjList = GetAdjList(S);
	Node* currNode = adjList->GetHead();
	while (currNode)
	{
		maxFlow += m_Matrix[S][currNode->GetData()].currentFlow;
		currNode = currNode->GetNext();
	}
	delete adjList;
	return maxFlow;
}

void AdjancencyMatrix::copyOnlyPostiveMaxFlowEdges(const AdjancencyMatrix& i_Other)
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
}

void AdjancencyMatrix::addAntiEdges()
{
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
				this->m_Matrix[j][i].residualFlow = this->m_Matrix[j][i].maxFlow - this->m_Matrix[j][i].currentFlow;
			}
		}
	}
}


List* AdjancencyMatrix::GetAdjList(int i_U) const
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

List* AdjancencyMatrix::GetAdjListByResidual(int i_U) const
{
	List* AdjList = new List();
	for (int i = 0; i < m_NumOfVertex; i++)
	{
		if (m_Matrix[i_U][i].isExist && m_Matrix[i_U][i].residualFlow != 0)
		{
			if(m_Matrix[i_U][i].maxFlow != 0 || m_Matrix[i][i_U].currentFlow != 0) // lo anti makbila 
				AdjList->InsertToTail(i);

		}
	}

	return AdjList;
}

