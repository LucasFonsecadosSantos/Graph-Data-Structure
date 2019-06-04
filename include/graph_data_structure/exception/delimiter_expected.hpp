#ifndef DELIMITER_EXPECTED_H
#define DELIMITER_EXPECTED_H

#include <exception>

class DelimiterExpected : public std::exception {
    
    public:
        DelimiterExpected(unsigned row, unsigned column) {
            this->column = column;
            this->row = row;
        }
        const char* what() const noexcept{ return m_error; }
    
    private:
        unsigned column;
        unsigned row;
        //const char* m_error = "INPUT FILE: " + std::to_string(row) + ":" + std::to_string(column) + "A name identifier expected at file syntax.";
        const char* m_error = "INPUT FILE: A type identifier expected at file syntax.";
};

#endif