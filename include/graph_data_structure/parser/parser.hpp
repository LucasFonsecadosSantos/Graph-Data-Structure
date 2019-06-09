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
        std::vector<Token*>* analyze();
        std::vector<Token*>* getEdgeSet();
        std::vector<Token*>* getVertexSet();
        std::vector<std::string>* getGraph(std::string description);
        Token *getGraphType();
        Token *getGraphAttr();
        Token *getGraphName();
        void setGraph(std::string graph);
        typedef struct {
            unsigned row;
            unsigned column;
        }ANALYZE_LOCATION;
        typedef struct {
            bool graphType;
            bool openDelimiter;
            bool closeDelimiter;
            bool graphName;
            bool graphAttr;
            bool vertexAnalyzing;
            bool edgeAnalyzing;
        } FLAG;
    
    private:
        char *delimiters;
        std::string *graphTypeIdentifiers;
        std::string *graphATTRIdentifiers;
        std::string graph;
        bool isGraphTypeIdentifier(std::string *identifier);
        bool isGraphATTRIdentifier(std::string *identifier);
        bool isGraphDelimiterIdentifier(std::string *identifier);
        FLAG getFlags();
        ANALYZE_LOCATION getAnalyzeLocation();
};

#endif