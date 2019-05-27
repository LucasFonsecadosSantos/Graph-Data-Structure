#ifndef NAME_IDENTIFIER_EXPECTED_H
#define NAME_IDENTIFIER_EXPECTED_H 1

#include <exception>

class NameIdentifierExpected : public std::exception {
     
    public:
        NameIdentifierExpected(unsigned row, unsigned column) {
            this->column = column;
            this->row = row;
        }
        const char* what() const noexcept{ return m_error; }
    
    private:
        unsigned column;
        unsigned row;
        const char* m_error = "INPUT FILE: " + std::to_string(row) + ":" + std::to_string(column) + "A name identifier expected at file syntax.";
};

#endif