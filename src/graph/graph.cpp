#include "../../include/graph_data_structure/graph/graph.hpp"
#include <string>
#include <cstddef>
#include <map>

Graph::Graph() {
    //this->adjacencyMatrix = this->weightMatrix = this->vertices = NULL;
}

Graph::Graph(bool **adjacencyMatrix) {
    //this->weightMatrix = this->vertices = NULL;
    setAdjacencyMatrix(adjacencyMatrix);
}

Graph::Graph(short **weightMatrix) {
    //this->adjacencyMatrix = this->vertices = NULL;
    setWeightMatrix(weightMatrix);
}

Graph::Graph(const char *filePath) {
    
}

Graph::~Graph() {}

void Graph::setAdjacencyMatrix(bool **adjacencyMatrix) {}

void Graph::setWeightMatrix(short **weightMatrix) {}

Graph::STATUS Graph::addVertex(std::string vertex) {}

Graph::STATUS Graph::addEdge(std::string vertex1, std::string vertex2) {}

std::string Graph::getName() {
    return this->name;
}

void Graph::setName(std::string name) {
    this->name = name;
}

bool Graph::containsVertex(std::string vertex) {

}

bool Graph::containsEdge(std::string vertex1, std::string vertex2) {
    
}