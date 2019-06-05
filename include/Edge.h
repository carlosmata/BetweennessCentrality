#ifndef EDGE_H
#define EDGE_H

//#include "Node.h"

class Node;
class Edge
{
    public:
        Edge();
        Edge(Node *endpoint, int cost);
        virtual ~Edge();

        Node* getEndpoint();
        int getCost();

    protected:

    private:
        int cost;
        Node *endpoint;
};

#endif // EDGE_H
