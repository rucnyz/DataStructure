#include <iostream>
#include "ALGraph.h"

extern Flight flight[2350];
int main()
{

	string input = R"(C:\Users\nieyuzhou\CLionProjects\DataStructure\Flight_Scheduling\flight_data.csv)";
	HandleOriginData(input);// flight[2500]

	ALGraph graph;
	graph.DFS(1);
	cout << 1;

//	ArcNode *p = G.vertices[47].firstArc;
	return 0;
}