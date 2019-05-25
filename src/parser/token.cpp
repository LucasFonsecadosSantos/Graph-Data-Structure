#include "../../include/graph_data_structure/parser/token.hpp"
#include "../../include/graph_data_structure/graph/graph.hpp"
#include <string>

Token::Token(Graph::TOKEN_TAG tag, std::string value) {
    setTag(tag);
    setValue(value);
}

Token::~Token() {
    delete this;
}

inline void Token::setValue(std::string value) {
    this->value = value;
}

inline std::string Token::getValue() {
    return this->value;
}

inline void Token::setTag(Graph::TOKEN_TAG tag) {
    this->tag = tag;
}

inline Graph::TOKEN_TAG Token::getTag() {
    return this->tag;
}