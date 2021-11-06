#include <iostream>
#include <string>
#include <exception>
#include "LinkerException.hpp"

LinkerException::LinkerException(std::string msg) : msg(msg) {

}