#include "MaxFlow.h"

int main(int argc, char* argv[])
{
	MaxFlow AlgoFinal(argc, argv);
	AlgoFinal.RunByBFS();
	AlgoFinal.RunByDijkstra();
}

//����� ������//
//====================== ����� ������   =========================== //
	//5-t (maxflow == 0) ��� ����� �� ��� �����
	//��� ���� ����� ����� ����� ���? ��� �� ���� ���� ���� ����� ��� ��� ��� �����?
	//���� ������?
	//#include <algorithm> <string>
	// ================================================================== //
	//Efficiency in PDF

