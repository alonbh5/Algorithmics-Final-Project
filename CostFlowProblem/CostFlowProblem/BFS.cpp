#include "BFS.h"

BFS::BFS(int i_NumOfVertices)
{
	this->m_Degree = new int(i_NumOfVertices);
	this->m_Parent = new int(i_NumOfVertices);
	this->m_Size = i_NumOfVertices;
}


void BFS::createBFSTree(AdjancencyMatrix& i_Graph, int i_S)
{
	int u, currVertex;
	Queue Q(m_Size * 2);
	initialize(Q, i_S, u);

	while (!Q.isEmpty())
	{
		u = Q.DeQueue();
		List* adjList = i_Graph.GetAdjListByResidual(u);
		Node* currNode = adjList->GetHead();
		while (currNode)
		{
			currVertex=currNode->GetData();
			if (m_Degree[currVertex] == Infinity)
			{
				m_Degree[currVertex] = m_Degree[u] + 1;
				m_Parent[currVertex] = u;
				Q.EnQueue(currVertex);
			}
			currNode = currNode->GetNext();
		}
		delete adjList;
	}
}

void BFS::initialize(Queue& io_Q, int& io_S, int& io_U)
{
	for (int i = 0; i < m_Size; i++)
	{
		m_Degree[i] = Infinity;
		m_Parent[i] = Infinity;
	}
	io_Q.EnQueue(io_S);
	m_Degree[io_S] = 0;
	io_U = 0;
}


List* BFS::FindImprovePath(int i_T)
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

List* BFS::MinCutGroupS(int i_S) //change for check
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

List* BFS::MinCutGroupT(int i_T)
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
