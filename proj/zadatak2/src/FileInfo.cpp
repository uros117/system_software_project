#include "FileInfo.hpp"
#include <iostream>
#include "SectionManager.hpp"
#include "SymbolTable.hpp"

FileInfo::FileInfo(std::string filename) : filename(filename) {
    
}

FileInfo::FileInfo() : FileInfo("") {

}

std::ostream& operator<<(std::ostream& out, FileInfo& obj) {
    out << obj.st;
    out << obj.sm;
    return out;
}

std::istream& operator>>(std::istream& in, FileInfo& obj) {
    // Temporary buffers
            std::string s1;
            int n1;

            int id;
            std::string name;
            int isGlobal;
            int isExtern;
            int offset;
            std::string section;
            int hasValue;

            int locationCounter;

            int count;

            int type;
            //std::string symb_name;
            int symb_id;
            int addend;

            int data;

            // Get the number of symbols
            in >> s1 >> std::hex >> n1;

            // Skip the table header
            in >> s1 >> s1 >> s1 >> s1 >> s1 >> s1 >> s1;

            // Load symbols
            for (int i = 0; i < n1; i++)
            {
                in >> id >> name >> isGlobal >> isExtern >> offset >> section >> hasValue;
                obj.st.symbolAdd(name, isGlobal, isExtern, section, hasValue, offset);
            }
            
            // Load section count
            in >> s1 >> n1;

            for (int i = 0; i < n1; i++)
            {
                // General informaiton
                in >> s1 >> name;
                in >> s1 >> offset;
                in >> s1 >> locationCounter;

                obj.sm.beginSection(name);
                obj.sm.getCurrent()->setOffset(offset);
                obj.sm.getCurrent()->setLocationCounter(locationCounter);

                // RelTable
                in >> s1 >> count;

                if(count > 0) in >> s1 >> s1 >> s1 >> s1;
                for (int j = 0; j < count; j++)
                {
                    in >> offset >> type >> symb_id >> addend;
                    obj.sm.getCurrent()->getRelTable().append(offset, type, symb_id, addend);
                }
                
                // Data
                in >> s1 >> count;

                for (int j = 0; j < count; j++)
                {
                    if(j % 8 == 0) {
                        in >> s1;
                    }
                    in >> data;
                    obj.sm.getCurrent()->appendData(data);
                }
            }
    return in;
}