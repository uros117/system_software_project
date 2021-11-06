#include <iostream>
#include <string>
#include <exception>
#include "AssemblerException.hpp"

AssemblerException::AssemblerException(std::string msg) : msg(msg) {

}