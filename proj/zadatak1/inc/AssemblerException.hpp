#ifndef __AssemblerException_HPP__
#define __AssemblerException_HPP__
#include <iostream>
#include <string>
#include <exception>

using namespace std;
class AssemblerException : public exception {
public:
    std::string msg;
    AssemblerException(std::string msg);
    ~AssemblerException() throw() {};
    virtual const char* what() const throw()
    {
        return msg.c_str();
    }
};

#endif