#ifndef TOKEN_PARSER_H
#define TOKEN_PARSER_H 1

#include "../graph/graph.hpp"
#include <string>

class Token {

    public:
        Token(Graph::TOKEN_TAG tag, std::string value);
        ~Token();
        inline void setValue(std::string value);
        inline std::string getValue();
        inline void setTag(Graph::TOKEN_TAG tag);
        inline Graph::TOKEN_TAG getTag();

    private:
        Graph::TOKEN_TAG tag;
        std::string value;
};

#endif