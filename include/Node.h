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
        void incrementCentrality(double increment);
        double getCentrality();
        void setVisited(bool visited);
        bool isVisited();
        void setDistance(int distance);
        int getDistance();
        void setParent(Node* parent);
        void addParent(Node* parent);
        vector<Node*> getParents();

    private:
        int id;
        vector<Edge*> edges;
        //To centrality
        double centrality;
        bool visited;
        int distance;
        vector<Node*> parents;
};

#endif // NODE_H
