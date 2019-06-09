#include "../../include/graph_data_structure/parser/parser.hpp"
#include "../../include/graph_data_structure/parser/token.hpp"
#include <iostream>

int main() {
    Parser *p = new Parser(
        "GRAPH Graph01 { b : c; c : d; }"
    );
    //std::vector<std::string> *v = p->getGraph("GRAPH Graph01 { b : c; c : d; } GRAPH Graph02 VALUED { b : c w[2];}");
    std::vector<Token*> *k = p->analyze();
    //std::cout << k->size();
    return 0;
}