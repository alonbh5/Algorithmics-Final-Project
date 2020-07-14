#include "AdjancencyMatrix.h"
#include "BFS.h"
#include <fstream>
using namespace std;

int FindMinResidual(List* i_Path, AdjancencyMatrix& i_Graph);
void MaximumFlowProblemByBFS(AdjancencyMatrix& i_Graph, int n, int m, int s, int t);
AdjancencyMatrix* createGraphFromFile(int& n, int& m, int& s, int& t, string file_name);
void printMaxFlowProblemResultBFS(BFS& myBFS, AdjancencyMatrix& GraphResult, AdjancencyMatrix& GraphResidual, int S, int T, int numOfIterations);

int main()
{
	int n, m, s, t;
	string file_name = "graph.txt";
	AdjancencyMatrix* Graph = createGraphFromFile(n, m, s, t, file_name);
	MaximumFlowProblemByBFS((*Graph), n,m,s-1,t-1); /// change to pointer graph
	delete Graph;
	return 0;

}

AdjancencyMatrix* createGraphFromFile(int& n, int& m, int& s, int& t, string file_name)
{
	ifstream in_file(file_name, ios::in);
	int vertexV, vertexU, weightEdge;
	if (!in_file)
		exit(-1);

	in_file >> n >> m >> s >> t;
	AdjancencyMatrix* Graph = new AdjancencyMatrix(n);

	for (int i = 0; i < m; i++)
	{
		in_file >> vertexV >> vertexU >> weightEdge;
		Graph->AddEdge(vertexV - 1, vertexU - 1, weightEdge);
	}
	return Graph;
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