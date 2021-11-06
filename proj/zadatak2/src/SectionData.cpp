#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "SectionData.hpp"
using namespace std;


SectionData::SectionData(std::string name) : name(name), offset(0), locationCounter(0), isPositioned(false) {
}

std::ostream& operator<<(std::ostream& out, SectionData& obj) {
    out << "Section: " << obj.name << endl;
    out << "Offset: " << obj.offset << endl;
    out << "LocCnt: " << obj.locationCounter << endl;

    out << obj.reltable;

    out<< "Data: " << obj.data.size();
    if(obj.data.size() > 0) {
        int i = 0;
        for(char b : obj.data) {
            if(i % 8 == 0) {
                out << endl;
                out << setfill('0') << setw(8) << right << hex << (unsigned int)i << setfill(' ') << ": ";
            }

            out << setfill('0') << setw(2) << right << hex << ((unsigned char)b & 0xff) << setfill(' ') << ' ';

            i++;
        }
        out << endl;
    } else out << endl;
    return out;
}

void SectionData::writeHex(std::ostream& out) {
    if(data.size() > 0) {
        int i = 0;
        for(char b : data) {
            if(i % 8 == 0) {
                out << endl;
                out << setfill('0') << setw(8) << right << hex << (unsigned int)(i + offset) << setfill(' ') << ": ";
            }

            out << setfill('0') << setw(2) << right << hex << ((unsigned char)b & 0xff) << setfill(' ') << ' ';

            i++;
        }
        out << endl;
    } else out << endl;
}