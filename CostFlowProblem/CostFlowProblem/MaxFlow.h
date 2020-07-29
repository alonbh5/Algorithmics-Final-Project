#ifndef _MAXFLOW_H_
#define _MAXFLOW_H_

#include "AdjancencyMatrix.h"
#include "BFS.h"
#include "Dijkstra.h"
#include <fstream>
#include <string>
#include <stdlib.h>
using namespace std;

class MaxFlow
{
private:
	AdjancencyMatrix* m_Graph;
	int m_NumOfVertex;
	int m_NumOfEdges;
	int m_StartVertex;
	int m_EndVertex;

public:
	MaxFlow(int argc, char* argv[]);
	~MaxFlow();
	void RunByBFS();
	void RunByDijkstra();

private:

	int findMinResidual(List* i_Path, AdjancencyMatrix& i_Graph);
	void addResidualFlowToEdgesOfTheImprovePath(List* i_ImprovePath, AdjancencyMatrix& io_GraphResidual, int& io_NumOfIterations);
	void getResultParametersByBFS(BFS& i_MyBFS, AdjancencyMatrix& io_GraphResidual, List*& o_MinCutS, List*& o_MinCutT, int& o_MaxFlow);
	void getResultParametersByDijkstra(Dijkstra& i_MyDijkstra, AdjancencyMatrix& io_GraphResidual, List*& o_MinCutS, List*& o_MinCutT, int& o_MaxFlow);
	void printResultOfMaxFlowProblem(List* i_GroupS, List* i_GroupT, int i_MaxFlow, int i_NumOfIterations, string i_MethodName) const;



	//file and validation functions
	void createGraphFromFile(string file_name);
	void getEdgesFromFile(ifstream& in_file);
	void checkValidVerticesAndWeightEdge(int i_VertexV, int i_VertexU, int i_WeightEdge, ifstream& in_file) const;
	void checkFile(ifstream& in_file, string file_name) const;
	void getAndCheckValidEntryInput(ifstream& in_file);

	//Utils
	void ltrim(string& io_str);
	void rtrim(string& io_str);
	void trim(string& io_str);
	void checkIfLineContinesThreeTokens(ifstream& in_file);
	int getASingleValidInput(ifstream& in_file);
	bool isTheStringContainsOnlyDigits(string i_Str);
	void errorMsgAndExitProgram(ifstream& in_file) const;
};


#endif // !_MAXFLOW_H_