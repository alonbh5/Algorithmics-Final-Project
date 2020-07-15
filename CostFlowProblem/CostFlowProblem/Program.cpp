#include "Program.h"

program::program(int argc, char* argv[])
{
	string file_name = argv[1];
	m_Graph= createGraphFromFile(m_NumOfVertex, m_NumOfEdges, m_StartVertex, m_EndVertex, file_name);
}

program::~program()
{
	delete m_Graph;
}


void program::AlgoritmicFinal()
{		
	maximumFlowProblemByBFS((*m_Graph), m_NumOfVertex, m_NumOfEdges, m_StartVertex , m_EndVertex);
	maximumFlowProblemByDijkstra((*m_Graph), m_NumOfVertex, m_NumOfEdges, m_StartVertex, m_EndVertex);	
}

AdjancencyMatrix* program::createGraphFromFile(int& n, int& m, int& s, int& t, string file_name)
{
	int numOfEdges = 0;
	bool error = false;
	ifstream in_file(file_name, ios::in);
	int vertexV, vertexU, weightEdge;
	if (!in_file)
	{
		cout << "Cannot open the file: " << file_name << endl;
		exit(1);
	}

	in_file >> n >> m >> s >> t;
	AdjancencyMatrix* Graph = new AdjancencyMatrix(n);

	for (int i = 0; i < m || in_file.eof(); i++)
	{
		in_file >> vertexV >> vertexU >> weightEdge;
		
		if (vertexU > n || vertexU < 0 || vertexV > n || vertexV < 0 || weightEdge < 0 || vertexU == vertexV || Graph->GetMatrix()[vertexV - 1][vertexU - 1].isExist)
		{
			//cases:
			//	dual edges, negtive  weight, self-loop,undefined vertex
			error = true;
			break;
		}		
		Graph->AddEdge(vertexV - 1, vertexU - 1, weightEdge);
		numOfEdges++;
	}

	in_file.close();

	if (numOfEdges != m)
	{			
		error = true;
	}

	if (error)
	{
		cout << "Invalid Input!" << endl;
		exit(2);
	}

	s--; //First Vertex is 0 and not 1
	t--;
	
	return Graph;
}



//----------------------------------------------------------------//
void program::maximumFlowProblemByBFS(AdjancencyMatrix& Graph, int n, int m, int s, int t)
{
	BFS myBFS(n);
	AdjancencyMatrix GraphResidual(n);
	List* minCutS, *minCutT, *improvePath = nullptr;
	int numOfIterations = 0, maxFlow;
	GraphResidual.MakeGraphResidual(Graph);

	do {
		if (improvePath)
			delete improvePath;

		myBFS.RunBFS(GraphResidual, s);
		improvePath = myBFS.FindImprovePath(t);
		addResidualFlowToEdgesOfTheImprovePath(improvePath, GraphResidual, numOfIterations);
		
	} while (improvePath);

	getResultParametersByBFS(myBFS, GraphResidual, minCutS, minCutT, maxFlow, s, t);
	printResultOfMaxFlowProblem(minCutS, minCutT, maxFlow, numOfIterations, "BFS Method");
	if(minCutS)
		delete minCutS;
	if(minCutT)
		delete minCutT;
}

//----------------------------------------------------------------//
void program::maximumFlowProblemByDijkstra(AdjancencyMatrix& Graph, int n, int m, int s, int t)
{
	Dijkstra myDijkstra(n);
	AdjancencyMatrix GraphResidual(n);
	GraphResidual.MakeGraphResidual(Graph);
	List* improvePath = nullptr, *minCutS, *minCutT;
	int maxFlow, numOfIterations = 0;

	do {
		if (improvePath)
			delete improvePath;
		myDijkstra.RunDijkstra(GraphResidual, s);
		improvePath = myDijkstra.FindImprovePath(t);
		addResidualFlowToEdgesOfTheImprovePath(improvePath, GraphResidual, numOfIterations);
	} while (improvePath);

	getResultParametersByDijkstra(myDijkstra, GraphResidual, minCutS, minCutT, maxFlow, s, t);
	printResultOfMaxFlowProblem(minCutS, minCutT, maxFlow, numOfIterations, "Greddy Method");
	if (minCutS)
		delete minCutS;
	if (minCutT)
		delete minCutT;
}

void program::getResultParametersByBFS(BFS& i_MyBFS, AdjancencyMatrix& io_GraphResidual, List*& o_MinCutS, List*& o_MinCutT, int& o_MaxFlow, int i_S, int i_T)
{
	i_MyBFS.RunBFS(io_GraphResidual, i_S);
	o_MaxFlow = io_GraphResidual.MaxFlow(i_S);
	o_MinCutS = i_MyBFS.MinCutGroupS(i_S);
	o_MinCutT = i_MyBFS.MinCutGroupT(i_T);
}
void program::getResultParametersByDijkstra(Dijkstra& i_MyDijkstra, AdjancencyMatrix& io_GraphResidual, List*& o_MinCutS, List*& o_MinCutT, int& o_MaxFlow, int i_S, int i_T)
{
	i_MyDijkstra.RunDijkstra(io_GraphResidual, i_S);
	o_MaxFlow = io_GraphResidual.MaxFlow(i_S);
	o_MinCutS = i_MyDijkstra.MinCutGroupS(i_S);
	o_MinCutT = i_MyDijkstra.MinCutGroupT(i_T);
}

//----------------------------------------------------------------//

void program::addResidualFlowToEdgesOfTheImprovePath(List* i_ImprovePath, AdjancencyMatrix& io_GraphResidual, int& io_NumOfIterations)
{
	if (i_ImprovePath)
	{
		io_NumOfIterations++;
		int residualOfPath = findMinResidual(i_ImprovePath, io_GraphResidual);
		io_GraphResidual.AddFlow(i_ImprovePath, residualOfPath);
	}
}
//----------------------------------------------------------------//

int program::findMinResidual(List* i_Path, AdjancencyMatrix& i_Graph)
{
	Node* currentNode = i_Path->GetHead();	
	int min = 0, u, v;
	bool firstIteration = true;
	while (currentNode->GetNext())
	{
		u = currentNode->GetData();
		v = currentNode->GetNext()->GetData();
		if (firstIteration)
		{
			min = i_Graph.GetMatrix()[u][v].residualFlow;
			firstIteration = false;
		}
		else if(i_Graph.GetMatrix()[u][v].residualFlow < min)
		{
			min = i_Graph.GetMatrix()[u][v].residualFlow;
		}
		currentNode = currentNode->GetNext();
	}
	return min;
}

//----------------------------------------------------------------//

void program::printResultOfMaxFlowProblem(List* i_GroupS, List* i_GroupT, int i_MaxFlow, int i_NumOfIterations, string i_MethodName)
{
	cout << i_MethodName << endl;
	if (i_NumOfIterations == 0)
	{
		cout << "No Network Flow" << endl;
	}
	else
	{
		cout << "Max Flow = " << i_MaxFlow << endl;
		cout << "Min cut: S = " << *i_GroupS << " " << " T = " << *i_GroupT << endl;
		cout << "Number of iterations = " << i_NumOfIterations << endl;
	}
}

//----------------------------------------------------------------//
