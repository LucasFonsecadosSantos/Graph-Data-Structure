#ifndef PARSER_H
#define PARSER_H 1

#include "token.hpp"
#include <string>
#include <vector>
#include <cstddef>

class Parser {

    public:
        Parser();
        Parser(std::string graph);
        ~Parser();
        std::string getGraph();
        std::vector<Token*> *getEdgeSet();
        std::vector<Token*> *getVertexSet();
        std::vector<std::string>* getGraph(std::string description);
        Token *getGraphType();
        Token *getGraphAttr();
        Token *getGraphName();
        void setGraph(std::string graph);
    
    private:
        char *delimiters;
        std::string *graphTypeIdentifiers;
        std::string *graphATTRIdentifiers;
        std::string graph;
        bool isGraphTypeIdentifier(std::string identifier);
};

#endif