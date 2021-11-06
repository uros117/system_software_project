#ifndef __LinkerException_HPP__
#define __LinkerException_HPP__
#include <iostream>
#include <string>
#include <exception>

using namespace std;
class LinkerException : public exception {
public:
    std::string msg;
    LinkerException(std::string msg);
    ~LinkerException() throw() {};
    virtual const char* what() const throw()
    {
        return msg.c_str();
    }
};

#endif