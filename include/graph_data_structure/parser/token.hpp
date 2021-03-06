#ifndef TOKEN_PARSER_H
#define TOKEN_PARSER_H 1

#include "../graph/graph.hpp"
#include <string>

class Token {

    public:
        Token(Graph::TOKEN_TAG tag, std::string *value);
        Token(Graph::TOKEN_TAG tag);
        ~Token();
        inline void setValue(std::string *value);
        std::string* getValue();
        inline void setTag(Graph::TOKEN_TAG tag);
        Graph::TOKEN_TAG getTag();

    private:
        Graph::TOKEN_TAG tag;
        std::string *value;
};

#endif