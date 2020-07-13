#include "AdjugateMatrix.h"
#include "BFS.h"

void main(char args[])
{
	//file..

	int n = 6;
	int m = 10;
	int s = 1;
	int t = 6;

	AdjugateMatrix Graph(n);
	Graph.AddEdge(1, 2, 16);
	Graph.AddEdge(1, 3, 13);
	Graph.AddEdge(2, 3, 10);
	Graph.AddEdge(3, 2, 4);
	Graph.AddEdge(2, 4, 12);
	Graph.AddEdge(4, 3, 9);
	Graph.AddEdge(3, 5, 14);
	Graph.AddEdge(5, 4, 7);
	Graph.AddEdge(5, 6, 4);
	Graph.AddEdge(4, 6, 20);

	AdjugateMatrix GraphResidula = Graph;
	AdjugateMatrix GraphResult = Graph;
	GraphResult.InitFlow();
	BFS myBFS(n);
	myBFS.createBFS(GraphResidula, s);
	List improvePath = myBFS.findPath(s,t);
}
