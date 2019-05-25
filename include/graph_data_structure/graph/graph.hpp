#ifndef GRAPH_H
#define GRAPH_H 1

#include <map>
#include <string>

class Graph {

    public:
        enum TOKEN_TAG {
            _VERTEX_,
            _EDGE_,
            _GRAPH_TYPE_,
            _ATTR_
        };
        enum GRAPH_TYPE {
            _GRAPH_,
            _DIGRAPH_
        };
        enum STATUS {
            _SUCCESS_,
            _FAILURE_
        };
        Graph();
        Graph(bool **adjacencyMatrix);
        Graph(short **weightMatrix);
        Graph(const char *filePath);
        ~Graph();
        std::string getName();
        bool containsVertex(std::string vertex);
        bool containsEdge(std::string vertex1, std::string vertex2);
        void setName(std::string name);
        void setAdjacencyMatrix(bool **adjacencyMatrix);
        void setWeightMatrix(short **weightMatrix);
        STATUS addVertex(std::string vertex);
        STATUS addEdge(std::string vertex1, std::string vertex2);
    
    private:
        std::string name;
        bool **adjacencyMatrix;
        short **weightMatrix;
        std::map<std::string, unsigned> *vertices;

        
};

#endif