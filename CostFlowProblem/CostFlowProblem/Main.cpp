#include "MaxFlow.h"

int main(int argc, char* argv[])
{
	MaxFlow AlgoFinal(argc, argv);
	AlgoFinal.RunByBFS();
	AlgoFinal.RunByDijkstra();
}

//ניתוח יעילות//
//====================== שאלות לפורום   =========================== //
	//5-t (maxflow == 0) אין במקרה זה רשת זרימה
	//האם חייב להיות לפחות מסלול אחד? האם זה תקין שאין בכלל מסלול ואז אין רשת זרימה?
	//מותר סטרינג?
	//#include <algorithm> <string>
	// ================================================================== //
	//Efficiency in PDF

