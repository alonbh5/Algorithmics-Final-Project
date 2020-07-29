#include "MaxFlow.h"
#include <algorithm>

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

void MaxFlow::getAndCheckValidEntryInput(ifstream& in_file)
{

	m_NumOfVertex = getASingleValidInput(in_file);
	m_NumOfEdges = getASingleValidInput(in_file);
	m_StartVertex = getASingleValidInput(in_file);
	m_EndVertex = getASingleValidInput(in_file);

	if (m_NumOfVertex < 1 || m_NumOfEdges >(m_NumOfVertex * m_NumOfVertex) || m_NumOfEdges < 0 || m_StartVertex > m_NumOfVertex || m_StartVertex < 1 || m_EndVertex > m_NumOfVertex || m_EndVertex < 1)
	{
		errorMsgAndExitProgram(in_file);
	}
}


void MaxFlow::createGraphFromFile(string file_name)
{
	ifstream in_file(file_name, ios::in);
	checkFile(in_file, file_name);
	getAndCheckValidEntryInput(in_file);
	m_Graph = new AdjancencyMatrix(m_NumOfVertex);
	getEdgesFromFile(in_file);
	in_file.close();
}

void MaxFlow::checkValidVerticesAndWeightEdge(int i_VertexV, int i_VertexU, int i_WeightEdge, ifstream& in_file) const
{
	if (i_VertexU > m_NumOfVertex || i_VertexU < 0 || i_VertexV > m_NumOfVertex || i_VertexV < 0 || i_WeightEdge < 0 || i_VertexU == i_VertexV || m_Graph->GetMatrix()[i_VertexV][i_VertexU].isExist)
	{
		errorMsgAndExitProgram(in_file);
	}
}

void MaxFlow::checkFile(ifstream& in_file, string file_name) const
{
	if (!in_file)
	{
		cout << "Cannot open the file: " << file_name << endl;
		exit(1);
	}
}

int MaxFlow::getASingleValidInput(ifstream& in_file)
{	
	string currLine;
	getline(in_file, currLine); 
	trim(currLine);
	if (!isTheStringContainsOnlyDigits(currLine))
	{
		errorMsgAndExitProgram(in_file);
	}
	return atoi(currLine.c_str());
}

bool MaxFlow::isTheStringContainsOnlyDigits(string i_Str)
{
	if (!i_Str.empty() && std::all_of(i_Str.begin(), i_Str.end(), ::isdigit))
	{
		return true;
	}
	return false;
}

void MaxFlow::checkIfLineContinesThreeTokens(ifstream& in_file)
{
	int countNumOfString = 0;
	bool flag = true;
	char* token, * currLineAsChars;
	string currLineAsString;

	getline(in_file, currLineAsString);
	trim(currLineAsString);
	currLineAsChars = strdup(currLineAsString.c_str());
	token = strtok(currLineAsChars, " ");

	while (token != NULL)
	{
		countNumOfString++;
		if (!isTheStringContainsOnlyDigits(token))
		{
			errorMsgAndExitProgram(in_file);
			flag = false;
			break;
		}
		token = strtok(NULL, " ");
	}

	if (countNumOfString != 3 || !flag)
	{
		errorMsgAndExitProgram(in_file);
	}
}

void MaxFlow::trim(string& io_str)
{
	ltrim(io_str);
	rtrim(io_str);
}

void MaxFlow::ltrim(string& io_str)
{
	char WHITESPACE = ' ';
	int len = io_str.length();
	for (int i = 0; i < len; i++)
	{
		if (io_str[i] != WHITESPACE)
		{
			io_str.erase(0, i);
			break;
		}
	}
}

void MaxFlow::rtrim(string& io_str)
{
	char WHITESPACE = ' ';
	int len = io_str.length();
	for (int  i = len-1; i >= 0; i--)
	{
		if (io_str[i] != WHITESPACE)
		{
			int begin = i + 1;
			int end = len - 1;
			io_str.erase(begin, end);
			break;
		}
	}
}

void MaxFlow::errorMsgAndExitProgram(ifstream& in_file) const
{
	in_file.close();
	cout << "Invalid Input!" << endl;
	exit(1);
}

void MaxFlow::getEdgesFromFile(ifstream& in_file)
{
	int currNumOfEdges = 0, vertexV, vertexU, weightEdge;
	string extraData, EMPTYSTRING = "";
	streampos currFilePosition;
	for (int i = 0; i < m_NumOfEdges && !in_file.eof(); i++)
	{
		currFilePosition= in_file.tellg();
		checkIfLineContinesThreeTokens(in_file);
		in_file.seekg(currFilePosition);
		in_file >> vertexV >> vertexU >> weightEdge;
		getline(in_file, extraData);
		checkValidVerticesAndWeightEdge(vertexV-1, vertexU-1, weightEdge, in_file);
		m_Graph->AddEdge(vertexV - 1, vertexU - 1, weightEdge);
		currNumOfEdges++;
	}

	in_file >> extraData;
	if (currNumOfEdges != m_NumOfEdges || extraData!= EMPTYSTRING)
	{
		errorMsgAndExitProgram(in_file);
	}
}



//----------------------------------------------------------------//
void MaxFlow::RunByBFS()
{
	BFS myBFS(m_NumOfVertex);
	AdjancencyMatrix GraphResidual(m_NumOfVertex); //n2
	List* minCutS, *minCutT, *improvePath = nullptr;
	int numOfIterations = 0, maxFlow;
	GraphResidual.MakeGraphResidual(*m_Graph); //n2

	do {
		if (improvePath)
			delete improvePath;

		myBFS.RunBFS(GraphResidual, m_StartVertex); //n+m = n2
		improvePath = myBFS.FindImprovePath(m_EndVertex); //n
		addResidualFlowToEdgesOfTheImprovePath(improvePath, GraphResidual, numOfIterations); //n
		
	} while (improvePath); //n

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
		myDijkstra.RunDijkstra(GraphResidual, m_StartVertex); //-(n+m)logn
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

void MaxFlow::printResultOfMaxFlowProblem(List* i_GroupS, List* i_GroupT, int i_MaxFlow, int i_NumOfIterations, string i_MethodName) const
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
