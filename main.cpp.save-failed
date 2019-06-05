#include <iostream>
#include "Graph.h"

using namespace std;

int  readNumberOfNodes(string filename);

int main(int argc, char **argv)
{
    string filename = "datasets/test.txt";
    Graph *g = new Graph(filename);

    if(g->getNumberNodes() > 0)
    {
        cout << "Number of Nodes: " << g->getNumberNodes() << endl;
        g->computeCentrality();
        cout << "Centrality: " << endl;
        g->printCentrality();
    }
    else
        cout << "Data null in the dataset";

    delete g;
}

