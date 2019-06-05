#include "Edge.h"

Edge::Edge()
{
    this->cost = 0;
    this->endpoint = 0;
}

Edge::Edge(Node *endpoint, int cost)
{
    this->cost = cost;
    this->endpoint = endpoint;
}

Edge::~Edge()
{

}
/**
    Get the endpoint of the edge
*/
Node* Edge::getEndpoint()
{
    return this->endpoint;
}
/**
    Get the cost of the edge
*/
int Edge::getCost()
{
    return this->cost;
}
