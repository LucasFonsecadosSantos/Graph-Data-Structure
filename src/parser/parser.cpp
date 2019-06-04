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
    std::string tmpString = "";
    bool typeFlag = false;
    bool wordOccurrencyFlag = false;
    unsigned row = 0;
    unsigned column = 0;
    
    for (unsigned i = 0; i < size; ++i) {
        tmpChar = this->graph.at(i);
        ++column;
        if ((tmpChar == ' ') && (tmpString == "")) {
            continue;
        } else if (tmpChar != ' '){
            tmpString += tmpChar;
        } else if ((tmpChar == ' ') && (tmpString != "")) {
            if (isGraphTypeIdentifier(tmpString)) {
                return new Token(Graph::TOKEN_TAG::_GRAPH_TYPE_,tmpString);
            } else {
                //Throw a exception: Graph type identifier expected;
            }
        }
    }
}

Token* Parser::getGraphName() {

}

Token* Parser::getGraphAttr() {

}

std::vector<std::string>* Parser::getGraph(std::string description) {
    unsigned limit = description.size();
    char tmpChar;
    std::string tmpStr;
    std::string graphStr;
    std::vector<std::string> *graphs = new std::vector<std::string>();
    bool openGraphFLAG = false;
    bool closeGraphFLAG = false;
    bool nameGraphFLAG = false;
    bool attrGraphFLAG = false;
    bool typeGraphFLAG = false;
    unsigned row = 0;
    unsigned column = 0;
    
    for (unsigned i = 0; i < limit; ++i) {
        tmpChar = description.at(i);
        ++column;
        if (tmpChar == '{') {
            if (typeGraphFLAG && nameGraphFLAG) {
                openGraphFLAG = true;
                tmpStr += tmpChar;
            } else {
                if (!typeGraphFLAG) {
                    throw TypeIdentifierExpected(row,column);
                } else {
                    throw NameIdentifierExpected(row,column);
                }
            }
        } else if (tmpChar == '}') {
            if (openGraphFLAG) {
                tmpStr += tmpChar;
                graphStr += tmpStr;
                graphs->push_back(graphStr);
                graphStr = "";
                tmpStr = "";
            } else {
                //EXECAO: NAO ABRIU O OBJ GRAFO
            }
        } else if (tmpChar == ' ') {
            if (tmpStr == "") {
                continue;
            } else {
                if (isGraphTypeIdentifier(tmpStr)) {
                    typeGraphFLAG = true;
                } else {
                    nameGraphFLAG = true;
                }
                graphStr += ' ' + tmpStr;
                tmpStr = "";
            }
        } else {
            tmpStr += tmpChar;
            if (tmpChar == '\0') {
                ++row;
                column = 0;
            }
        }
    }
    return graphs;
}

bool Parser::isGraphTypeIdentifier(std::string identifier) {
    unsigned short size = this->graphTypeIdentifiers->size();
    for (unsigned i = 0 ; i < size ; ++i)
        if (identifier == this->graphTypeIdentifiers[i])
            return true;
    return false;
}