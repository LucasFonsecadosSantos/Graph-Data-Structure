#include "../../include/graph_data_structure/parser/parser.hpp"
#include <iostream>

int main() {
    Parser *p = new Parser(
        "GRAPH Graph01 { b : c; c : d; } GRAPH Graph02 VALUED { b : c w[2];}"
    );
    std::vector<std::string> *v = p->getGraph("GRAPH Graph01 { b : c; c : d; } GRAPH Graph02 VALUED { b : c w[2];}");
    std::cout << p->getGraphType()->getValue();
    
    return 0;
}