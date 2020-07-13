#include "BFS.h"

BFS::BFS(int numOfVertexs)
{
	this->d = new int(numOfVertexs);
	this->p = new int(numOfVertexs);
	arrSize = numOfVertexs;
}

void BFS::createBFS(AdjugateMatrix& G, int s)
{
	initialize();
	Queue Q(arrSize*2);
	Q.EnQueue(s);
	d[s] = 0;
	int u = 0;

	while (!Q.isEmpty())
	{
		u = Q.DeQueue();
		List Adj = G.GetAdjListByResidual(u);
		Node* currNode = Adj.Head;
		int currVertex;

		while (currNode)
		{
			currVertex=currNode->data;
			if (d[currVertex] == INFINITY)
			{
				d[currVertex] = d[u] + 1;
				p[currVertex] = u;
				Q.EnQueue(currVertex);
			}
			currNode = currNode->next;
		}
	}
}

void BFS::initialize()
{
	for (int i = 0; i < arrSize; i++)
	{
		d[i] = INFINITY;
		p[i] = INFINITY;
	}

}


List BFS::findPath(int s, int t)
{
	List path;
	int currV = t;
	if (p[t] != INFINITY)
	{
		path.InsertToHead(t);
		while (p[currV] != INFINITY)
		{
			path.InsertToHead(p[currV]);
			currV = p[currV];
		}
	}
	return path;
}
