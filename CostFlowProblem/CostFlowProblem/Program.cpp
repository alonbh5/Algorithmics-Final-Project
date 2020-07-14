#include "AdjancencyMatrix.h"
#include "BFS.h"
#include <fstream>
using namespace std;

int FindMinResidual(List* i_Path, AdjancencyMatrix& i_Graph);
void MaximumFlowProblemByBFS(AdjancencyMatrix& i_Graph, int n, int m, int s, int t);
void createGraphFromFile(AdjancencyMatrix& Grpah);
void printMaxFlowProblemResultBFS(BFS& myBFS, AdjancencyMatrix& GraphResult, AdjancencyMatrix& GraphResidual, int S, int T, int numOfIterations);

void main()
{
	//file..
	int n = 6;
	int m = 10;
	int s = 0;
	int t = 5;
	AdjancencyMatrix Graph(n);
	createGraphFromFile(Graph);
	MaximumFlowProblemByBFS(Graph, n,m,s,t);

}


void createGraphFromFile(AdjancencyMatrix& Graph)
{
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
}



//----------------------------------------------------------------//
void MaximumFlowProblemByBFS(AdjancencyMatrix& Graph, int n, int m, int s, int t)
{
	BFS myBFS(n);
	AdjancencyMatrix GraphResidual(n);
	GraphResidual.MakeGraphResidual(Graph);
	List* improvePath = nullptr;
	int residualOfPath;
	int numOfIterations = 0;

	do {
		if (improvePath != nullptr)
			delete improvePath;

		myBFS.createBFSTree(GraphResidual, s);
		improvePath = myBFS.FindImprovePath(t);
		if (!improvePath->IsEmpty())
		{
			numOfIterations++;
			residualOfPath = FindMinResidual(improvePath, GraphResidual);
			GraphResidual.AddFlow(improvePath, residualOfPath);
		}
	} while (!improvePath->IsEmpty());

	AdjancencyMatrix GraphResult = Graph;
	GraphResult.InitFlow();
	GraphResult.CopyOnlyFlowEdges(GraphResidual);

	printMaxFlowProblemResultBFS(myBFS,GraphResult,GraphResidual,s,t,numOfIterations);

}

void printMaxFlowProblemResultBFS(BFS& myBFS, AdjancencyMatrix& GraphResult, AdjancencyMatrix& GraphResidual, int S, int T, int numOfIterations)
{
	//GraphResult.PrintEdges();

	//----------------------------//
	myBFS.createBFSTree(GraphResidual, S);
	List* minCutS = myBFS.MinCutGroupS(S);
	List* minCutT = myBFS.MinCutGroupT(T);
	int maxFlow = GraphResult.MaxFlow(S);
	cout << "BFS Methods" << endl;
	cout << "Max Flow = " << maxFlow << endl;
	cout << "Min Cut: S= "; // CHANGE TO OPERATOR <<
	minCutS->PrintList();	// CHANGE TO OPERATOR <<
	cout << "Min Cut: T= ";// CHANGE TO OPERATOR <<
	minCutT->PrintList();	// CHANGE TO OPERATOR <<
	cout << endl;
	cout << "Number of iterations = " << numOfIterations << endl;
	//----------------------------//
	delete minCutS;
	delete minCutT;
}
int FindMinResidual(List* i_Path, AdjancencyMatrix& i_Graph)
{
	Node* currentNode = i_Path->GetHead();	
	int min;
	int u, v;

	min = 10000000; // CHANGEIT

	while (currentNode->m_Next)
	{
		u = currentNode->m_Data;
		v = currentNode->m_Next->m_Data;
		if (i_Graph.m_Matrix[u][v].ResidualFlow < min)
		{
			min = i_Graph.m_Matrix[u][v].ResidualFlow;
		}
		currentNode = currentNode->m_Next;
	}
	return min;
}
