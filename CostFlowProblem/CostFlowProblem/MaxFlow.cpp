#include "MaxFlow.h"

MaxFlow::MaxFlow(int argc, char* argv[])
{
	string file_name = argv[1];
	createGraphFromFile(file_name);
	m_StartVertex--; //First Vertex is 0 and not 1
	m_EndVertex--;
}

MaxFlow::~MaxFlow()
{
	delete m_Graph;
}

void MaxFlow::checkValidEntryInput(ifstream in_file)
{
	in_file >> m_NumOfVertex >> m_NumOfEdges >> m_StartVertex >> m_EndVertex;

	if (m_NumOfVertex < 1 || m_NumOfEdges >(m_NumOfVertex * m_NumOfVertex) || m_NumOfEdges < 0 || m_StartVertex > m_NumOfVertex || m_StartVertex < 1 || m_EndVertex > m_NumOfVertex || m_EndVertex < 1)
	{
		in_file.close();
		cout << "Invalid Input!" << endl;
		exit(1);
	}
}


void MaxFlow::createGraphFromFile(string file_name)
{
	ifstream in_file(file_name, ios::in);
	checkFile(in_file, file_name);
	in_file >> m_NumOfVertex >> m_NumOfEdges >> m_StartVertex >> m_EndVertex; 
	m_Graph = new AdjancencyMatrix(m_NumOfVertex);
	getEdgesFromFile(in_file);
	in_file.close();
}

void MaxFlow::checkValidVerticesAndWeightEdge(int i_VertexV, int i_VertexU, int i_WeightEdge, ifstream& in_file)
{
	if (i_VertexU > m_NumOfVertex || i_VertexU < 0 || i_VertexV > m_NumOfVertex || i_VertexV < 0 || i_WeightEdge < 0 || i_VertexU == i_VertexV || m_Graph->GetMatrix()[i_VertexV - 1][i_VertexU - 1].isExist)
	{
		in_file.close();
		cout << "Invalid Input!" << endl;
		exit(1);
	}
}

void MaxFlow::checkFile(ifstream& in_file, string file_name)
{
	if (!in_file)
	{
		cout << "Cannot open the file: " << file_name << endl;
		exit(1);
	}
}

void MaxFlow::getEdgesFromFile(ifstream& in_file)
{
	int currNumOfEdges = 0, vertexV, vertexU, weightEdge;

	for (int i = 0; i < m_NumOfEdges || in_file.eof(); i++)
	{
		in_file >> vertexV >> vertexU >> weightEdge;
		checkValidVerticesAndWeightEdge(vertexV, vertexU, weightEdge, in_file);
		m_Graph->AddEdge(vertexV - 1, vertexU - 1, weightEdge);
		currNumOfEdges++;
	}
	if (currNumOfEdges != m_NumOfEdges)
	{
		in_file.close();
		cout << "Invalid Input!" << endl;
		exit(1);
	}
}



//----------------------------------------------------------------//
void MaxFlow::RunByBFS()
{
	BFS myBFS(m_NumOfVertex);
	AdjancencyMatrix GraphResidual(m_NumOfVertex);
	List* minCutS, *minCutT, *improvePath = nullptr;
	int numOfIterations = 0, maxFlow;
	GraphResidual.MakeGraphResidual(*m_Graph);

	do {
		if (improvePath)
			delete improvePath;

		myBFS.RunBFS(GraphResidual, m_StartVertex);
		improvePath = myBFS.FindImprovePath(m_EndVertex);
		addResidualFlowToEdgesOfTheImprovePath(improvePath, GraphResidual, numOfIterations);
		
	} while (improvePath);

	getResultParametersByBFS(myBFS, GraphResidual, minCutS, minCutT, maxFlow);
	printResultOfMaxFlowProblem(minCutS, minCutT, maxFlow, numOfIterations, "BFS Method");
	if(minCutS)
		delete minCutS;
	if(minCutT)
		delete minCutT;
}



//----------------------------------------------------------------//
void MaxFlow::RunByDijkstra()
{
	Dijkstra myDijkstra(m_NumOfVertex);
	AdjancencyMatrix GraphResidual(m_NumOfVertex);
	GraphResidual.MakeGraphResidual((*m_Graph));
	List* improvePath = nullptr, *minCutS, *minCutT;
	int maxFlow, numOfIterations = 0;

	do {
		if (improvePath)
			delete improvePath;
		myDijkstra.RunDijkstra(GraphResidual, m_StartVertex);
		improvePath = myDijkstra.FindImprovePath(m_EndVertex);
		addResidualFlowToEdgesOfTheImprovePath(improvePath, GraphResidual, numOfIterations);
	} while (improvePath);

	getResultParametersByDijkstra(myDijkstra, GraphResidual, minCutS, minCutT, maxFlow);
	printResultOfMaxFlowProblem(minCutS, minCutT, maxFlow, numOfIterations, "Greddy Method");
	if (minCutS)
		delete minCutS;
	if (minCutT)
		delete minCutT;
}

void MaxFlow::getResultParametersByBFS(BFS& i_MyBFS, AdjancencyMatrix& io_GraphResidual, List*& o_MinCutS, List*& o_MinCutT, int& o_MaxFlow)
{
	i_MyBFS.RunBFS(io_GraphResidual, m_StartVertex);
	o_MaxFlow = io_GraphResidual.MaxFlow(m_StartVertex);
	o_MinCutS = i_MyBFS.MinCutGroupS(m_StartVertex);
	o_MinCutT = i_MyBFS.MinCutGroupT(m_EndVertex);
}
void MaxFlow::getResultParametersByDijkstra(Dijkstra& i_MyDijkstra, AdjancencyMatrix& io_GraphResidual, List*& o_MinCutS, List*& o_MinCutT, int& o_MaxFlow)
{
	i_MyDijkstra.RunDijkstra(io_GraphResidual, m_StartVertex);
	o_MaxFlow = io_GraphResidual.MaxFlow(m_StartVertex);
	o_MinCutS = i_MyDijkstra.MinCutGroupS(m_StartVertex);
	o_MinCutT = i_MyDijkstra.MinCutGroupT(m_EndVertex);
}

//----------------------------------------------------------------//

void MaxFlow::addResidualFlowToEdgesOfTheImprovePath(List* i_ImprovePath, AdjancencyMatrix& io_GraphResidual, int& io_NumOfIterations)
{
	if (i_ImprovePath)
	{
		io_NumOfIterations++;
		int residualOfPath = findMinResidual(i_ImprovePath, io_GraphResidual);
		io_GraphResidual.AddFlow(i_ImprovePath, residualOfPath);
	}
}
//----------------------------------------------------------------//

int MaxFlow::findMinResidual(List* i_Path, AdjancencyMatrix& i_Graph)
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

void MaxFlow::printResultOfMaxFlowProblem(List* i_GroupS, List* i_GroupT, int i_MaxFlow, int i_NumOfIterations, string i_MethodName)
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
