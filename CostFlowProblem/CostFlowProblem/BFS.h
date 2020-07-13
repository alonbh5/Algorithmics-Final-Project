#pragma once

#include "Queue.h"
#include "AdjugateMatrix.h"
#include "List.h"
#define INFINITY 1


class BFS
{
private:
	int* d;
	int* p;
	int arrSize;


	void initialize();

public:
	BFS(int numOfvertexs);
	void createBFS(AdjugateMatrix G, int s);
	List findPath(int s, int t);
};

