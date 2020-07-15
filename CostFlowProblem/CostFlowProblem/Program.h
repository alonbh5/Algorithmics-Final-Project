#pragma once
//need to be class?

#include "AdjancencyMatrix.h"
#include "BFS.h"
#include "Dijkstra.h"
#include <fstream>
#include <stdlib.h>
using namespace std;

class program
{
private:

	AdjancencyMatrix* m_Graph;
	int m_NumOfVertex;
	int m_NumOfEdges;
	int m_StartVertex;
	int m_EndVertex;

public:
	program(int argc, char* argv[]);
	~program();
	void AlgoritmicFinal();

private:
	
	
	AdjancencyMatrix* createGraphFromFile(int& n, int& m, int& s, int& t, string file_name);
	void maximumFlowProblemByBFS(AdjancencyMatrix& i_Graph, int n, int m, int s, int t);
	void maximumFlowProblemByDijkstra(AdjancencyMatrix& Graph, int n, int m, int s, int t);
	//AuxilaryFunction
	int findMinResidual(List* i_Path, AdjancencyMatrix& i_Graph);
	void addResidualFlowToEdgesOfTheImprovePath(List* i_ImprovePath, AdjancencyMatrix& io_GraphResidual, int& io_NumOfIterations);
	void getResultParametersByBFS(BFS& i_MyBFS, AdjancencyMatrix& io_GraphResidual, List*& o_MinCutS, List*& o_MinCutT, int& o_MaxFlow, int i_S, int i_T);
	void getResultParametersByDijkstra(Dijkstra& i_MyDijkstra, AdjancencyMatrix& io_GraphResidual, List*& o_MinCutS, List*& o_MinCutT, int& o_MaxFlow, int i_S, int i_T);
	void printResultOfMaxFlowProblem(List* i_GroupS, List* i_GroupT, int i_MaxFlow, int i_NumOfIterations, string i_MethodName);
};