#include "AdjancencyMatrix.h"
#include "BFS.h"
#include <fstream>
using namespace std;

AdjancencyMatrix& createGraphFromFile(int& n, int& m, int& s, int& t, string file_name);
int findMinResidual(List* i_Path, AdjancencyMatrix& i_Graph);
void maximumFlowProblemByBFS(AdjancencyMatrix& i_Graph, int n, int m, int s, int t);
void printMaxFlowProblemResultBFS(BFS& myBFS, AdjancencyMatrix& GraphResult, AdjancencyMatrix& GraphResidual, int S, int T, int numOfIterations);

int main()
{
	int n, m, s, t;
	string file_name = "graph.txt";
	AdjancencyMatrix Graph = createGraphFromFile(n, m, s, t, file_name);
	maximumFlowProblemByBFS((Graph), n,m,s-1,t-1); /// change to pointer graph
	//delete Graph;
	return 0;

	//fix problem sometimes in the end of the main or when i print max flow;
}

AdjancencyMatrix& createGraphFromFile(int& n, int& m, int& s, int& t, string file_name)
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

	in_file.close();
	return *Graph;
}



//----------------------------------------------------------------//
void maximumFlowProblemByBFS(AdjancencyMatrix& Graph, int n, int m, int s, int t)
{
	BFS myBFS(n);
	AdjancencyMatrix GraphResidual(n), GraphResult(n);
	GraphResidual.MakeGraphResidual(Graph);
	List* improvePath = nullptr;
	int residualOfPath, numOfIterations = 0;

	do {
		if (improvePath != nullptr)
			delete improvePath;

		myBFS.createBFSTree(GraphResidual, s);
		improvePath = myBFS.FindImprovePath(t);
		if (!improvePath->IsEmpty())
		{
			numOfIterations++;
			residualOfPath = findMinResidual(improvePath, GraphResidual);
			GraphResidual.AddFlow(improvePath, residualOfPath);
		}
	} while (!improvePath->IsEmpty());

	GraphResult.CopyOnlyFlowEdges(GraphResidual);
	printMaxFlowProblemResultBFS(myBFS,GraphResult,GraphResidual,s,t,numOfIterations);
}

void printMaxFlowProblemResultBFS(BFS& myBFS, AdjancencyMatrix& GraphResult, AdjancencyMatrix& GraphResidual, int S, int T, int numOfIterations)
{
	int maxFlow;
	//GraphResult.PrintEdges();
	myBFS.createBFSTree(GraphResidual, S);
	List* minCutS = myBFS.MinCutGroupS(S);
	List* minCutT = myBFS.MinCutGroupT(T);
	maxFlow = GraphResult.MaxFlow(S);
	cout << "BFS Methods" << endl;
	cout << "Max Flow = " << maxFlow << endl;
	cout << "Min Cut: S= " << minCutS << ". " << "MinCutT: T= " << *minCutT << endl;
	cout << "Number of iterations = " << numOfIterations << endl;
	delete minCutS;
	delete minCutT;
}

int findMinResidual(List* i_Path, AdjancencyMatrix& i_Graph)
{
	Node* currentNode = i_Path->GetHead();	
	int min;
	int u, v;

	min = 10000000; // CHANGEIT

	while (currentNode->GetNext())
	{
		u = currentNode->GetData();
		v = currentNode->GetNext()->GetData();
		if (i_Graph.m_Matrix[u][v].ResidualFlow < min)
		{
			min = i_Graph.m_Matrix[u][v].ResidualFlow;
		}
		currentNode = currentNode->GetNext();
	}
	return min;
}
