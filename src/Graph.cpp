#include "Graph.h"

Graph::Graph(string filename)
{
    int n = this->readNumberOfNodes(filename);
    //Create the nodes
    this->numberNodes = n;
    this->nodes = new Node*[numberNodes];
    for(int i = 0; i < numberNodes; i++){
        this->nodes[i] = new Node(i);
    }
    //create the nodes
    this->addEdges(filename);
}

Graph::Graph(int numberNodes)
{
    this->numberNodes = numberNodes;
    this->nodes = new Node*[numberNodes];
    for(int i = 0; i < numberNodes; i++){
        this->nodes[i] = new Node(i);
    }
}

Graph::~Graph()
{
    for (int i=0; i<this->numberNodes; i++)
        delete this->nodes[i];
    delete[] this->nodes;
}

/**
    Add an edge from nodeI to nodeJ
*/
void Graph::addEdge(int nodeI, int nodeJ, int cost)
{
    if(nodeI < this->numberNodes && nodeJ < this->numberNodes){
        this->nodes[nodeI]->addEdge(this->nodes[nodeJ], cost);
    }
}

/**
    Add all the edges from a dataset
*/
bool Graph::addEdges(string filename)
{
    string line, number = "";
    ifstream dataset;
    size_t found;
    string stringFind = "FromNodeId";

    int counter = 1, nodei, nodej;

    dataset.open(filename);

    if(dataset.is_open()){
        while(getline(dataset, line)){
             if(line.length() > 0){
                if(line.at(0) == '#'){
                    found = line.find(stringFind);
                    if (found != string::npos){ //The word is inside of the line
                        //Add edges
                        while(getline(dataset, line)){
                            //read the nodei and the nodej
                            counter = 1;
                            nodei = nodej = this->numberNodes;

                            for(unsigned int i = 0; i < line.length();i++){
                                if(isdigit(line[i])){
                                    number = "";
                                    while(isdigit(line[i]) && i < line.length()){
                                        number += line[i];
                                        i++;
                                    }
                                }
                                if(counter == 1)
                                    nodei = stoi(number);
                                else if(counter == 2)
                                    nodej = stoi(number);
                                else
                                    break;

                                counter++;
                            }

                            //Add the edge
                            if(nodei < this->numberNodes && nodej < this->numberNodes){
                                this->addEdge(nodei, nodej, 1);
                            }
                            //////
                        }
                    }
                }
             }
        }
        dataset.close();
    }
    else{
        return false;
    }


    return true;
}

/**
    Get the number of nodes
*/
int Graph::getNumberNodes()
{
    return this->numberNodes;
}

/**
    Get the numbers of nodes of the data set
*/
int Graph::readNumberOfNodes(string filename)
{
    int numbersOfNode = -1;
    string line, stringFind, number = "";
    ifstream dataset;
    size_t found;
    stringFind = "Nodes:";

    dataset.open(filename);
    if(dataset.is_open()){
        while(getline(dataset, line)){
            if(line.length() > 0){
                if(line.at(0) == '#'){
                    found = line.find(stringFind);
                    if (found != string::npos){ //The word is inside of the line
                        //Find the number
                        for(unsigned int i = found + stringFind.length(); i < line.length();i++){
                            if(isdigit(line[i])){
                                while(isdigit(line[i]) && i < line.length()){
                                    number += line[i];
                                    i++;
                                }
                                break;
                            }
                        }
                        //Convert the number to integer
                        numbersOfNode = stoi(number);
                        break;
                    }
                }
            }
        }
        dataset.close();
    }
    else{
        cout << "Unable to open the data set";
        return -1;
    }

    return numbersOfNode;
}

/**
    Compute the centrality of all nodes in the Graph
*/
void Graph::computeCentrality()
{
    //Reset the centrality existent
    for(int i= 0; i < this->numberNodes; i++){
        this->nodes[i]->resetCentrality();
    }

    //Compute the new centrality
    for(int i= 0; i < this->numberNodes; i++){
        this->dijkstra(this->nodes[i]);
        for(int j= 0; j < this->numberNodes; j++){
            this->computeCentralityPath(this->nodes[i], this->nodes[j], this->nodes[j]->getParents().size());
        }
    }
 }
/**
    Compute the Dijkstra algorithm to find the shortest path from the node source to
*/
 void Graph::dijkstra(Node* source)
 {
    Edge* edge;
    vector<Edge*>::iterator ptr;
    int cost = 0, totalcost = 0;
    Node* node = nullptr, *endpoint = nullptr;

    //First reset the values parent, distance, and visited
    for(int i= 0; i < this->numberNodes; i++){
        this->nodes[i]->resetValues();
    }
    source->setDistance(0);

    while((node = this->getSmallDistance()) != nullptr){
        for(unsigned int i = 0; i < node->getEdges().size(); i++){
            edge = node->getEdges()[i];
            endpoint = edge->getEndpoint();

            if(endpoint != nullptr && !endpoint->isVisited()){
                cost = edge->getCost();
                totalcost = cost + node->getDistance();
                if(totalcost < endpoint->getDistance()){ //Add only one path
                    endpoint->setDistance(totalcost);
                    endpoint->setParent(node);
                }
                else if(totalcost == endpoint->getDistance()){ //Add other shortest path
                    endpoint->addParent(node);
                }
            }
        }
        node->setVisited(true);
        //Put the centrality HERE
        //this->computeCentralityPath(source, node, node->getParents().size()); ?? put here??
    }

 }

 /**
    Compute the centrality of a path from a source and a tail
 */
 void Graph::computeCentralityPath(Node* source, Node* tail, unsigned int n_shortest_path)
 {
     Node* parent = nullptr;

     if(tail != source){
         for(unsigned int i = 0; i < tail->getParents().size(); i++){
             parent = tail->getParents()[i];
             if(parent != source){
                float incremento = 1.0/n_shortest_path;
                parent->incrementCentrality(incremento);
             }
             this->computeCentralityPath(source, parent, n_shortest_path); //* tail->getParents().size() ??
         }
     }
 }

/**
    Get the node's small distance in the graph
*/
 Node* Graph::getSmallDistance()
 {
    Node* smallDistance = nullptr;
    int mini = std::numeric_limits<int>::max();
    for(int i= 0; i < this->numberNodes; i++){
        if(!this->nodes[i]->isVisited() && this->nodes[i]->getDistance() < mini){
            mini = this->nodes[i]->getDistance();
            smallDistance = this->nodes[i];
        }
    }

    return smallDistance;
 }

void Graph::printCentrality()
{
    for(int i= 0; i < this->numberNodes; i++){
        cout<< "Node: " << this->nodes[i]->getId()
            << " Centrality:" << this->nodes[i]->getCentrality() / 2 << endl;
    }
}
