/************************************************************************/
/* $Id: MainP.cpp 65 2010-09-08 06:48:36Z yan.qi.asu $                                                                 */
/************************************************************************/

#include <limits>
#include <set>
#include <map>
#include <queue>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "GraphElements.h"
#include "Graph.h"
#include "DijkstraShortestPathAlg.h"
#include "YenTopKShortestPathsAlg.cpp"

using namespace std;


void testDijkstraGraph()
{
	Graph* my_graph_pt = new Graph("../data/nsfnet");
	DijkstraShortestPathAlg shortest_path_alg(my_graph_pt);
	BasePath* result =
		shortest_path_alg.get_shortest_path(
			my_graph_pt->get_vertex(0), my_graph_pt->get_vertex(5));
	result->PrintOut(cout);
}

void testYenAlg()
{
	Graph my_graph("../testing/nsfnet");
	ofstream fp;
	fp.open("../paths/test/5.txt");

    for(int i = 0; i <= 7; i++)
    {
        for(int j = 0; j <= 7 ;j++)
        {
            YenTopKShortestPathsAlg yenAlg(my_graph, my_graph.get_vertex(i),my_graph.get_vertex(j));
			if(i != j){
            int c=0;
            while(yenAlg.has_next())
            {
                ++c;
                yenAlg.next()->PrintOut(fp);
            }
		}
        }
    }
    fp.close();
}

int main(...)
{
	cout << "Welcome to the real world!" << endl;
	testYenAlg();
	//testDijkstraGraph();
}
