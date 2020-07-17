#include "MaxFlow.h"

int main(int argc, char* argv[])
{
	MaxFlow AlgoFinal(argc, argv);
	AlgoFinal.RunByBFS();
	AlgoFinal.RunByDijkstra();
}

////====================== שאלות לפורום   =========================== //
	//האם לאפשר משקלים שלילים? 
	//5-t (maxflow == 0) אין במקרה זה רשת זרימה
	//האם חייב להיות לפחות מסלול אחד? האם זה תקין שאין בכלל מסלול ואז אין רשת זרימה?
	//מסמך ללא פרמטרים מיותרים בסוף או משהו כזה.	
	//מותר סטרינג?
	// ================================================================== //
	//relax - make it shorter
	//Recheck The function - Const, Good Naming, Code Reuse and Efficiency of the methods.
	//Arrange the Program class - mayble to open AUXILARY Class with all the other methods (or put them as static function in the classes)


	//Check all the 5 inputs write inside the PDF
	//Efficiency in PDF