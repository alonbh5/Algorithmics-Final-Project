#include "AdjugateMatrix.h"
#include "BFS.h"


int findMinResidual(List& path, AdjugateMatrix& graph);

void main(char args[])
{
	//file..

	int n = 6;
	int m = 10;
	int s = 0;
	int t = 5;
	List improvePath;
	BFS myBFS(n);
	AdjugateMatrix Graph(n);


	Graph.AddEdge(0, 1, 16);
	Graph.AddEdge(0, 2, 13);
	Graph.AddEdge(1, 2, 10);
	Graph.AddEdge(2, 1, 4);
	Graph.AddEdge(1, 3, 12);
	Graph.AddEdge(3, 2, 9);
	Graph.AddEdge(2, 4, 14);
	Graph.AddEdge(4, 3, 7);
	Graph.AddEdge(4, 5, 4);
	Graph.AddEdge(3, 5, 20);

	AdjugateMatrix GraphResidual(n);
	GraphResidual.MakeGraphResidual(Graph);
	GraphResidual.PrintEdges();
	AdjugateMatrix GraphResult = Graph;
	GraphResult.InitFlow();
	int residualOfPath;


	do {		
		myBFS.createBFS(GraphResidual, s);
		improvePath = myBFS.findPath(s, t);

		if (!improvePath.IsEmpty())
		{
			residualOfPath = findMinResidual(improvePath, GraphResidual);
			GraphResidual.AddFlow(improvePath, residualOfPath);
		}
	} while (!improvePath.IsEmpty());

	GraphResult.CopyOnlyFlowEdges(GraphResidual);
	std::cout << std::endl;
	GraphResult.PrintEdges();
}

int findMinResidual(List& path, AdjugateMatrix& graph)
{
	Node* currentNode = path.Head;	
	int min;
	int u, v;

	min = 10000000;

	while (currentNode->next)
	{
		u = currentNode->data;
		v = currentNode->next->data;

		if (graph.m_Matrix[u][v].ResidualFlow < min)
		{
			min = graph.m_Matrix[u][v].ResidualFlow;
		}

		currentNode = currentNode->next;
	}

	return min;
}
