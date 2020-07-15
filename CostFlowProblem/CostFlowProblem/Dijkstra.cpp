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

void Dijkstra::RunDijkstra(AdjancencyMatrix& i_Graph, int i_S)
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
			if (m_Degree[vertexU] != Infinity)
			{
				relax(vertexU, vertexV, i_S, i_Graph, Q);
			}
			currNode = currNode->GetNext();

		}
		delete AdjList;
	}
	//cout << "==============" << endl;
	//for (int i = 0; i < m_Size; i++)
	//{
	//	cout << i << ": " << m_Degree[i] << " ";
	//}
	//cout << endl << endl;
	//for (int i = 0; i < m_Size; i++)
	//{
	//	cout << i << ": " << m_Parent[i] << " ";
	//}
	//cout << endl << endl;


}

void Dijkstra::relax(int i_U, int i_V, int i_S, AdjancencyMatrix& Graph, HeapMax& Q)
{
	int val;
	int loctionInHeap = Q.FindPlaceOfKey(i_V);


	if (m_Degree[i_V] == Infinity && i_U == i_S)
	{
		m_Degree[i_V] = Graph.GetMatrix()[i_U][i_V].residualFlow;
		m_Parent[i_V] = i_U;
		Q.IncreaseKey(loctionInHeap, m_Degree[i_V]);
	}
	else if (m_Degree[i_V] == Infinity && i_U != i_S)
	{
		if (m_Degree[i_U] < Graph.GetMatrix()[i_U][i_V].residualFlow)
		{
			val = m_Degree[i_U];
		}
		else
		{
			val = Graph.GetMatrix()[i_U][i_V].residualFlow;
		}
		m_Degree[i_V] = val;
		m_Parent[i_V] = i_U;
		Q.IncreaseKey(loctionInHeap, m_Degree[i_V]);
	}
	else
	{
		if (m_Degree[i_U] < Graph.GetMatrix()[i_U][i_V].residualFlow)
		{
			val = m_Degree[i_U];
		}
		else
		{
			val = Graph.GetMatrix()[i_U][i_V].residualFlow;
		}

		if (m_Degree[i_V] < val && i_V != i_S)
		{
			m_Degree[i_V] = val;
			m_Parent[i_V] = i_U;
			Q.IncreaseKey(loctionInHeap, m_Degree[i_V]);
		}
	}
}





void Dijkstra::initialize(const int i_S)
{
	for (int i = 0; i < m_Size; i++)
	{
		m_Degree[i] = Infinity;
		m_Parent[i] = Infinity;
	}
	m_Degree[i_S] = 0;
	
}



List* Dijkstra::FindImprovePath(const int i_T) 
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
		//cout << *path << endl;
	}
	return path;
}

List* Dijkstra::MinCutGroupS(const int i_S)  //change for check
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

List* Dijkstra::MinCutGroupT(const int i_T)
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
