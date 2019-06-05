#ifndef NODE_H
#define NODE_H

#include "Edge.h"
#include <iostream>
#include <vector>
#include <limits>

using namespace std;

class Node
{
    public:
        Node(int id);
        virtual ~Node();

        void addEdge(Node *endpoint, int cost);
        void resetValues();

        vector<Edge*> getEdges();

        int getId();
        void resetCentrality();
        void incrementCentrality();
        int getCentrality();
        void setVisited(bool visited);
        bool isVisited();
        void setDistance(int distance);
        int getDistance();
        void setParent(Node* parent);
        Node* getParent();

        //void dijkstra();

    private:
        int id;
        vector<Edge*> edges;
        //To centrality
        int centrality;
        bool visited;
        int distance;
        Node* parent;
};

#endif // NODE_H
