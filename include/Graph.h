#ifndef GRAPH_H
#define GRAPH_H

#include "Node.h"
#include <fstream>
#include <limits>
#include <iostream>
#include <vector>

class Graph
{
    public:
        Graph(string filename);
        Graph(int numberNodes);
        virtual ~Graph();

        void addEdge(int nodeI, int nodeJ, int cost);
        bool addEdges(string filename);
        int getNumberNodes();
        void computeCentrality();
        void printCentrality();

    protected:

    private:
        int numberNodes;
        Node **nodes;
        void dijkstra(Node* source);
        int readNumberOfNodes(string filename);
        Node* getSmallDistance();
        void computeCentralityPath(Node* source, Node* tail);

};

#endif // GRAPH_H
