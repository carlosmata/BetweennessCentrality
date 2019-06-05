#include "Node.h"

Node::Node(int id)
{
    this->id = id;
    this->centrality = 0;
    this->resetValues();
}

Node::~Node()
{
    for (unsigned int i = 0; i < this->edges.size(); i++) {
        delete this->edges[i];
    }
}
/**
    Add an edge from this node and other node whit a cost
*/
void Node::addEdge(Node *endpoint, int cost)
{
    Edge *edge = new Edge(endpoint, cost);
    this->edges.push_back(edge);
}

/**
    Reset the values to compute the centrality
*/
void Node::resetValues()
{
    this->visited = false;
    this->distance = std::numeric_limits<int>::max();
    this->parent = nullptr;
}

/**
    reset the centrality
*/
void Node::resetCentrality()
{
    this->centrality = 0;
}

/**
    Get the Id in the node
*/
int Node::getId()
{
    return this->id;
}

/**
    Increment the centrality 1 by 1
*/
void Node::incrementCentrality()
{
    this->centrality++;
}

/**
    Get the centrality of the node
*/
int Node::getCentrality()
{
    return centrality;
}
/**
    Set the value to visited
*/
void Node::setVisited(bool visited)
{
    this->visited = visited;
}
/**
    Get if the node is visited
*/
bool Node::isVisited()
{
    return this->visited;
}
/**
    Set a distance in the node
*/
void Node::setDistance(int distance)
{
    this->distance = distance;
}
/**
    Get the distance in the node
*/
int Node::getDistance()
{
    return this->distance;
}
/**
    Set the parent to the shortest path
*/
void Node::setParent(Node* parent)
{
    this->parent = parent;
}
/**
    Get the parent to the shortest path
*/
Node* Node::getParent()
{
    return this->parent;
}
/**
    Get the edges of the node
*/
vector<Edge*> Node::getEdges()
{
    return this->edges;
}

