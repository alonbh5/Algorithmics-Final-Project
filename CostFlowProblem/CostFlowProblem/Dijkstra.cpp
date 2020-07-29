#include "Dijkstra.h"



Dijkstra::Dijkstra(int i_NumOfVertices)
{
	this->m_MaxFlowFromS = new int[i_NumOfVertices];
	this->m_Parent = new int[i_NumOfVertices];
	this->m_Size = i_NumOfVertices;
}

Dijkstra::~Dijkstra()
{
	delete[] m_MaxFlowFromS;
	delete[] m_Parent;
}

void Dijkstra::RunDijkstra(AdjancencyMatrix& i_Graph, int i_S)
{
	initialize(i_S);
	int vertexU, vertexV;
	HeapMax Q(m_Size);
	List* AdjList;
	Node* currNode;
	Q.Build(m_MaxFlowFromS, m_Size);

	while (!Q.IsEmpty())
	{
		vertexU = Q.DeleteMax();
		AdjList = i_Graph.GetAdjListByResidual(vertexU);
		currNode = AdjList->GetHead();
		while (currNode)
		{
			vertexV = currNode->GetData();
			if (m_MaxFlowFromS[vertexU] != Infinity)
			{
				relax(vertexU, vertexV, i_S, i_Graph, Q);
			}
			currNode = currNode->GetNext();

		}
		delete AdjList;
	}
}

void Dijkstra::relax(int i_U, int i_V, int i_S, AdjancencyMatrix& Graph, HeapMax& Q)
{
	int val;	
	int loctionInHeap = Q.FindPlaceOfKey(i_V);
	bool shouldUpdate = false;

	if (m_MaxFlowFromS[i_U] < Graph.GetMatrix()[i_U][i_V].residualFlow && i_U != i_S)
	{
		val = m_MaxFlowFromS[i_U];
	}
	else
	{
		val = Graph.GetMatrix()[i_U][i_V].residualFlow;
	}

	if (m_MaxFlowFromS[i_V] == Infinity)
	{
		shouldUpdate = true;
	}
	else if (m_MaxFlowFromS[i_V] < val && i_V != i_S)
	{
		shouldUpdate = true;
	}

	if (shouldUpdate)
	{
		m_MaxFlowFromS[i_V] = val;
		m_Parent[i_V] = i_U;
		Q.IncreaseKey(loctionInHeap, m_MaxFlowFromS[i_V]);
	}
}

void Dijkstra::initialize(const int i_S)
{
	for (int i = 0; i < m_Size; i++)
	{
		m_MaxFlowFromS[i] = Infinity;
		m_Parent[i] = Infinity;
	}
	m_MaxFlowFromS[i_S] = 0;	
}


List* Dijkstra::FindImprovePath(const int i_T) const
{
	List* path = nullptr;
	int currV = i_T;
	if (m_Parent[i_T] != Infinity)
	{
		path = new List();
		path->InsertToHead(i_T);
		while (m_Parent[currV] != Infinity)
		{
			path->InsertToHead(m_Parent[currV]);
			currV = m_Parent[currV];
		}	
	}

	return path;
}

List* Dijkstra::MinCutGroupS(const int i_S) const
{
	List* minCutGroupS = new List();
	for (int i = 0; i < m_Size; i++)
	{
		if (m_MaxFlowFromS[i] != Infinity)
		{
			minCutGroupS->InsertToTail(i + 1);
		}
	}
	return minCutGroupS;
}

List* Dijkstra::MinCutGroupT(const int i_T) const
{
	List* minCutGroupT = new List();
	for (int i = 0; i < m_Size; i++)
	{
		if (m_MaxFlowFromS[i] == Infinity)
		{
			minCutGroupT->InsertToTail(i + 1);
		}
	}
	return minCutGroupT;
}
