#include "Program.h"

void AlgoritmicFinal(int argc, char* argv[])
{
	int n, m, s, t;
	string file_name = argv[1];
	AdjancencyMatrix* Graph = createGraphFromFile(n, m, s, t, file_name);	
	maximumFlowProblemByBFS((*Graph), n, m, s - 1, t - 1);
	maximumFlowProblemByDijkstra((*Graph), n, m, s - 1, t - 1);
	delete Graph;
	////====================== שאלות לפורום   =========================== //
	//האם לאפשר משקלים שלילים? 
	//5-t (maxflow == 0) אין במקרה זה רשת זרימה
	//האם חייב להיות לפחות מסלול אחד? האם זה תקין שאין בכלל מסלול ואז אין רשת זרימה?
	//מסמך ללא פרמטרים מיותרים בסוף או משהו כזה.	
	// ================================================================== //

	//Recheck The function - Const, Good Naming, Code Reuse and Efficiency of the methods.
	//Arrange the Program class - mayble to open AUXILARY Class with all the other methods (or put them as static function in the classes)

		
	//Check all the 5 inputs write inside the PDF
	//Efficiency in PDF
}

AdjancencyMatrix* createGraphFromFile(int& n, int& m, int& s, int& t, string file_name)
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

	
	return Graph;
}



//----------------------------------------------------------------//
void maximumFlowProblemByBFS(AdjancencyMatrix& Graph, int n, int m, int s, int t)
{
	BFS myBFS(n);
	AdjancencyMatrix GraphResidual(n);
	List* minCutS, *minCutT, *improvePath = nullptr;
	int numOfIterations = 0, maxFlow;
	GraphResidual.MakeGraphResidual(Graph);

	do {
		if (improvePath)
			delete improvePath;

		myBFS.createBFSTree(GraphResidual, s);
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
void maximumFlowProblemByDijkstra(AdjancencyMatrix& Graph, int n, int m, int s, int t)
{
	Dijkstra myDijkstra(n);
	AdjancencyMatrix GraphResidual(n);
	GraphResidual.MakeGraphResidual(Graph);
	List* improvePath = nullptr, *minCutS, *minCutT;
	int maxFlow, numOfIterations = 0;

	do {
		if (improvePath)
			delete improvePath;
		myDijkstra.createDijkstraTree(GraphResidual, s);
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

void getResultParametersByBFS(BFS& i_MyBFS, AdjancencyMatrix& io_GraphResidual, List*& o_MinCutS, List*& o_MinCutT, int& o_MaxFlow, int i_S, int i_T)
{
	i_MyBFS.createBFSTree(io_GraphResidual, i_S);
	o_MaxFlow = io_GraphResidual.MaxFlow(i_S);
	o_MinCutS = i_MyBFS.MinCutGroupS(i_S);
	o_MinCutT = i_MyBFS.MinCutGroupT(i_T);
}
void getResultParametersByDijkstra(Dijkstra& i_MyDijkstra, AdjancencyMatrix& io_GraphResidual, List*& o_MinCutS, List*& o_MinCutT, int& o_MaxFlow, int i_S, int i_T)
{
	i_MyDijkstra.createDijkstraTree(io_GraphResidual, i_S);
	o_MaxFlow = io_GraphResidual.MaxFlow(i_S);
	o_MinCutS = i_MyDijkstra.MinCutGroupS(i_S);
	o_MinCutT = i_MyDijkstra.MinCutGroupT(i_T);
}

//----------------------------------------------------------------//

void addResidualFlowToEdgesOfTheImprovePath(List* i_ImprovePath, AdjancencyMatrix& io_GraphResidual, int& io_NumOfIterations)
{
	if (i_ImprovePath)
	{
		io_NumOfIterations++;
		int residualOfPath = findMinResidual(i_ImprovePath, io_GraphResidual);
		io_GraphResidual.AddFlow(i_ImprovePath, residualOfPath);
	}
}
//----------------------------------------------------------------//

int findMinResidual(List* i_Path, AdjancencyMatrix& i_Graph)
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

void printResultOfMaxFlowProblem(List* i_GroupS, List* i_GroupT, int i_MaxFlow, int i_NumOfIterations, string i_MethodName)
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
