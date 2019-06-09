#include "../../include/graph_data_structure/parser/parser.hpp"
#include "../../include/graph_data_structure/parser/token.hpp"
#include "../../include/graph_data_structure/exception/delimiter_expected.hpp"
#include "../../include/graph_data_structure/exception/name_identifier_expected.hpp"
#include "../../include/graph_data_structure/exception/type_identifier_expected.hpp"

#include <cstddef>
#include <string>
#include <vector>
#include <iostream>

Parser::Parser(std::string graph) {
    this->delimiters = new char[6] {
        '{','}',':',';','[',']'
    };
    this->graphATTRIdentifiers = new std::string[2] {
        "DESCRIBED","VALUED"
    };
    this->graphTypeIdentifiers = new std::string[2] {
        "GRAPH","DIGRAPH"
    };
    setGraph(graph);
}

Parser::Parser() {
    this->delimiters = new char[6] {
        '{','}',':',';','[',']'
    };
    this->graphATTRIdentifiers = new std::string[2] {
        "DESCRIBED","VALUED"
    };
    this->graphTypeIdentifiers = new std::string[2] {
        "GRAPH","DIGRAPH"
    };
    setGraph(NULL);
}

Parser::~Parser() {
    delete this->delimiters;
    delete this->graphATTRIdentifiers;
    delete this->graphTypeIdentifiers;
    //this->delimiters = this->graphATTRIdentifiers = this->graphTypeIdentifiers = NULL;
    delete this;
}

std::string Parser::getGraph() {
    return this->graph;
}

void Parser::setGraph(std::string graph) {
    this->graph = graph;
}

Token* Parser::getGraphType() {
    unsigned size = this->graph.size();
    char tmpChar;
    std::string *tmpString = new std::string("");
    unsigned row = 0;
    unsigned column = 0;
    
    for (unsigned i = 0; i < size; ++i) {
        tmpChar = this->graph.at(i);
        ++column;
        if ((tmpChar == ' ') && (*tmpString == ""))
            continue;
        else if (tmpChar != ' ')
            *tmpString += tmpChar;
        else if ((tmpChar == ' ') && (*tmpString != ""))
            if (isGraphTypeIdentifier(tmpString))
                return new Token(Graph::TOKEN_TAG::_GRAPH_TYPE_,tmpString);
            //ELSE Throw a exception: Graph type identifier expected;
    }
}

Token* Parser::getGraphName() {
    unsigned size = this->graph.size();
    ANALYZE_LOCATION update = getAnalyzeLocation();
    FLAG flag = getFlags(); 
    char tmpChar;
    std::string *tmpString = new std::string("");
    unsigned row = 0;
    unsigned column = 0;
    
    for (unsigned i = 0; i < size; ++i) {
        tmpChar = this->graph.at(i);
        ++column;
        if ((tmpChar == ' ') && (*tmpString == "")) {
            continue;
        } else if ((tmpChar == ' ') && (*tmpString != "")) {
            if (isGraphTypeIdentifier(tmpString) && !flag.graphType) {
                flag.graphType = true;
                *tmpString = "";
            } else if (!isGraphDelimiterIdentifier(tmpString) && !isGraphATTRIdentifier(tmpString) && flag.graphType) {
                return new Token(Graph::TOKEN_TAG::_GRAPH_NAME_, tmpString);
            } else {
                //Thrown expcetion: Graph name token expected;
            }
        }
    }
}

std::vector<Token*>* Parser::analyze() {
    std::cout << "teste";
    ANALYZE_LOCATION update = getAnalyzeLocation();
    FLAG flag = getFlags();
    Token *tmpEdgeToken = new Token(Graph::TOKEN_TAG::_EDGE_, new std::string[2]()); 
    unsigned size = this->graph.size();
    char tmpChar;
    std::string *tmpStr = new std::string("");
    std::vector<Token*> *tokens = new std::vector<Token*>();

    
    for (unsigned i = 0; i < size; ++i) {
        tmpChar = this->graph.at(i);
        update.column++;
        if (tmpChar == ' ' && *tmpStr == "") {
            continue;
        } else if (flag.vertexAnalyzing && flag.openDelimiter) {
            if (tmpChar != ':') {
                *tmpStr += tmpChar;
            } else if (!flag.edgeAnalyzing) {
                tmpEdgeToken->getValue()[0] = *tmpStr;
                flag.edgeAnalyzing = true;
                *tmpStr = "";
            } else {
                tmpEdgeToken->getValue()[1] = *tmpStr;
                flag.edgeAnalyzing = flag.vertexAnalyzing = false;
                tokens->push_back(tmpEdgeToken);
                *tmpStr = "";
            }
        } else if (tmpChar == ' ' && *tmpStr != "") {
            std::cout << tmpChar;
            if (!flag.graphType) {
                if (isGraphTypeIdentifier(tmpStr)) {
                    flag.graphType = true;
                    tokens->push_back(new Token(Graph::TOKEN_TAG::_GRAPH_TYPE_,tmpStr));
                    *tmpStr = "";
                } else {
                    //exception: faltou o token tipo do grafo
                }
            } else if (flag.graphType && !flag.graphName) {
                if (isGraphATTRIdentifier(tmpStr)) {
                    //exception: faltou nome do grafo
                } else {
                    flag.graphName = true;
                    tokens->push_back(new Token(Graph::TOKEN_TAG::_GRAPH_NAME_,tmpStr));
                    *tmpStr = "";
                }
            } else if (flag.graphName && flag.graphType && !flag.graphAttr){
                if (isGraphATTRIdentifier(tmpStr)) {
                    flag.graphAttr = true;
                    tokens->push_back(new Token(Graph::TOKEN_TAG::_ATTR_,tmpStr));
                    *tmpStr = "";
                } else {
                    //exeception: UNKnow attr
                }
            }
        } else if (tmpChar == '{') {
            std::cout << tmpChar;
            if (!flag.graphName || !flag.graphType) {
                //exception: name token or type token expected
            } else {
                flag.vertexAnalyzing = flag.openDelimiter = true;
                *tmpStr = "";
            }
        } else if (tmpChar == '}') {
            if (flag.openDelimiter) {
                flag.closeDelimiter = true;
                //deu certo, pode encerrar a analize do grafo
            } else {
                //lancar execao, nao abriu o grafo
            }
        } else {
            std::cout << tmpChar;
            *tmpStr += tmpChar;
        }
    }
    return tokens;
}

Token* Parser::getGraphAttr() {

}

std::vector<std::string>* Parser::getGraph(std::string description) {
    unsigned limit = description.size();
    char tmpChar;
    std::string *tmpStr;
    std::string graphStr;
    std::vector<std::string> *graphs = new std::vector<std::string>();
    FLAG flag = getFlags();
    
    unsigned row = 0;
    unsigned column = 0;
    
    for (unsigned i = 0; i < limit; ++i) {
        tmpChar = description.at(i);
        ++column;
        if (tmpChar == '{') {
            if (flag.graphType && flag.graphName) {
                flag.openDelimiter = true;
                *tmpStr += tmpChar;
                if (!flag.graphType) {
                    throw TypeIdentifierExpected(row,column);
                } else {
                    throw NameIdentifierExpected(row,column);
                }
            }
        } else if (tmpChar == '}') {
            if (flag.openDelimiter) {
                *tmpStr += tmpChar;
                graphStr += *tmpStr;
                graphs->push_back(graphStr);
                graphStr = "";
                *tmpStr = "";
            } else {
                //EXECAO: NAO ABRIU O OBJ GRAFO
            }
        } else if (tmpChar == ' ') {
            if (*tmpStr == "") {
                continue;
            } else {
                if (isGraphTypeIdentifier(tmpStr)) {
                    flag.graphType = true;
                } else {
                    flag.graphName = true;
                }
                graphStr += ' ' + *tmpStr;
                *tmpStr = "";
            }
        } else {
            }
            *tmpStr += tmpChar;
            if (tmpChar == '\0') {
                ++row;
                column = 0;
            }
        }
    return graphs;
}

bool Parser::isGraphTypeIdentifier(std::string *identifier) {
    unsigned short size = this->graphTypeIdentifiers->size();
    for (unsigned short i = 0 ; i < size ; ++i)
        if (*identifier == this->graphTypeIdentifiers[i])
            return true;
    return false;
}

bool Parser::isGraphATTRIdentifier(std::string *identifier) {
    unsigned short size = this->graphATTRIdentifiers->size();
    for (unsigned short i = 0; i < size; ++i)
        if (*identifier == this->graphATTRIdentifiers[i])
            return true;
    return false;
}


bool Parser::isGraphDelimiterIdentifier(std::string *identifier) {
    unsigned short size = sizeof(this->delimiters);
    for (unsigned short i = 0; i < size; ++i)
        if (identifier->at(0) == this->delimiters[i])
            return true;
    return false;
}

Parser::ANALYZE_LOCATION Parser::getAnalyzeLocation() {
    return {0,0};
}

Parser::FLAG Parser::getFlags() {
    return {false, false, 
            false, false, 
            false, false, 
            false
    };
}