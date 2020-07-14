#include "Dijkstra.h"



Dijkstra::Dijkstra(int i_NumOfVertices)
{
	this->m_Degree = new int[i_NumOfVertices];
	this->m_Parent = new int[i_NumOfVertices];
	this->m_Size = i_NumOfVertices;
}

Dijkstra::~Dijkstra()
{
	delete[] m_Degree;
	delete[] m_Parent;
}

void Dijkstra::createDijkstraTree(AdjancencyMatrix& i_Graph, int i_S)
{
	initialize(i_S);
	int vertexU, vertexV;
	HeapMax Q(m_Size);
	List* AdjList;
	Node* currNode;
	Q.Build(m_Degree, m_Size);

	while (!Q.IsEmpty())
	{
		vertexU = Q.DeleteMax();
		AdjList = i_Graph.GetAdjListByResidual(vertexU);
		currNode = AdjList->GetHead();
		while (currNode)
		{
			vertexV = currNode->GetData();
			relax(vertexU, vertexV, i_S, i_Graph, Q);
			currNode = currNode->GetNext();
		}
		delete AdjList;
	}

}

void Dijkstra::relax(int i_U, int i_V, int i_S, AdjancencyMatrix& Graph, HeapMax& Q)
{

	if (m_Degree[i_V] < m_Degree[i_U] + Graph.m_Matrix[i_U][i_V].ResidualFlow && i_V != i_S, i_V != m_Parent[i_U]) 		
	{
		m_Degree[i_V] = m_Degree[i_U] + Graph.m_Matrix[i_U][i_V].ResidualFlow;	;
		m_Parent[i_V] = i_U;
		Q.IncreaseKey(i_V, m_Degree[i_V]); 
	}
}



void Dijkstra::initialize(int& i_S)
{
	for (int i = 0; i < m_Size; i++)
	{
		m_Degree[i] = Infinity;
		m_Parent[i] = Infinity;
	}
	m_Degree[i_S] = 0;
	
}



List* Dijkstra::FindImprovePath(int i_T)
{
	List* path = new List();
	int currV = i_T;
	if (m_Parent[i_T] != Infinity)
	{
		path->InsertToHead(i_T);
		while (m_Parent[currV] != Infinity)
		{
			path->InsertToHead(m_Parent[currV]);
			currV = m_Parent[currV];
		}
	}
	return path;
}

List* Dijkstra::MinCutGroupS(int i_S) //change for check
{
	List* minCutGroupS = new List();
	for (int i = 0; i < m_Size; i++)
	{
		if (m_Degree[i] != Infinity)
		{
			minCutGroupS->InsertToTail(i + 1);
		}
	}
	return minCutGroupS;
}

List* Dijkstra::MinCutGroupT(int i_T)
{
	List* minCutGroupT = new List();
	for (int i = 0; i < m_Size; i++)
	{
		if (m_Degree[i] == Infinity)
		{
			minCutGroupT->InsertToTail(i + 1);
		}
	}
	return minCutGroupT;
}
