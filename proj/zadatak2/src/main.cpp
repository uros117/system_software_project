#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <set>
#include <regex>
#include "FileInfo.hpp"
#include "SymbolTable.hpp"
#include "SectionManager.hpp"
#include "SymbolData.hpp"
#include "SectionData.hpp"
#include "LinkerException.hpp"

#define NONE (0)
#define HEX (1)
#define ELF (2)

#define RED ("\033[0;31m")
#define YEL ("\033[1;33m")
#define NC ("\033[0m")

struct PlaceData{
    std::string name;
    uint16_t place;
    PlaceData(std::string name, uint16_t place) : name(name), place(place) {

    }
    bool operator< (const PlaceData& e) const
    {
        return (place < e.place);
    }
};

std::list<FileInfo> files;
std::list<std::string> file_paths;

int main(int argc, char* argv[])
{
    int output = NONE;
    std::string output_filename = "";
    std::list<PlaceData> pd;
    // options
    for (int i = 1; i < argc; i++)
    {
        std::string arg(argv[i]);
        if(arg == "-o") {
            i++;
            if(i < argc) {
                output_filename = argv[i];
            } else {
                std::cout << RED << "Missing output file name!" << NC << std::endl;
                return -1;
            }
        } else if(arg == "-hex") {
            if(output == NONE)
                output = HEX;
            else {
                std::cout << RED << "Error output type already set!" << NC << std::endl;
                return -1;
            }
        } else if(arg == "-linkable") {
            if(output == NONE)
                output = ELF;
            else {
                std::cout << "Error output type already set!" << std::endl;
                return -1;
            }
        } else {
            std::string name;
            uint16_t place;
            std::string start = "-place=";
            char c1;
            
            if(arg.compare(0, start.length(), start) == 0) {
                std::stringstream ss(arg);
                name.clear();
                for(int i = 0; i < start.length(); i++)
                    ss.ignore();
                while(true) {
                    ss >> c1;
                    name.push_back(c1);
                    if (ss.peek() == '@') {
                        ss.ignore();
                        break;
                    }
                }

                ss.ignore();// 0
                ss.ignore();// x
                
                ss >> std::hex >> place;
                
                pd.push_back(PlaceData(name, place));
            } else {
                file_paths.push_back(argv[i]);
            }
        }
    }
    if(output == NONE || output_filename == "") {
        return 0;
    }
    
    std::cout << std::hex;

    for(std::string file_path : file_paths){
        std::ifstream in;
        in.open(file_path, std::ios::in);
        if(in.is_open()) {
            // Add a file info object to the list
            // and get its reference
            files.push_back(FileInfo(file_path));
            FileInfo& fi = files.back();

            in >> fi;

            //std::cout << fi;

            in.close();
        } else {
            std::cout << "Error occured while openning the input file" << std::endl;
            return -1;
        }
    }
    
    // Join sections
    FileInfo linked;
    for(FileInfo& i : files) {
        SectionManager& sm = linked.getSM();
        for(SectionData& sd : i.getSM().getList()) {
            sm.beginSection(sd.getName());
            SectionData& linkedSection = *sm.getCurrent();

            // Append relocation table with increased offset
            /*for(RelData& rd : sd.getRelTable().getTable()) {
                linkedSection.getRelTable().append(
                    rd.getOffset() + linkedSection.getLocationCounter(), 
                    rd.getType(), 
                    rd.getSymbName(), 
                    rd.getAddend());
            }*/

            // Append data
            for(unsigned char data : sd.getData()) {
                linkedSection.appendData(data);
            }

            // Set file info section offset so that the symbols will be able use it
            sd.setOffset(linkedSection.getLocationCounter());

            // Inrement location counter
            linkedSection.incLocationCounter(sd.getLocationCounter());
        }
    }

    // Generate symbol sets
    //std::set<SymbolData> u;
    //std::set<SymbolData> d;
    
    for(FileInfo& i : files) {
        for(SymbolData& sd : i.getST().getTable()) {
            linked.getST().linkSymbol(sd, i);
            /*if(sd.getIsGlobal() || (sd.getName() == sd.getSection())) {
                // The symbols is global or extern
                if(sd.getHasValue()) {
                    // Symbol defined
                    if(u.count(sd)) {
                        u.erase(sd);
                    }
                    if(d.count(sd)) {
                        std::cout << "Error symbol " << sd.getName() << " already defined!" << std::endl;
                        return -1;
                    } else {
                        SectionData* section = i.getSM().getSectionByName(sd.getSection());
                        if(!section) {
                            std::cout << RED << "Error while linking the symbol table, missing section: " << sd.getSection() << "!" << NC << std::endl;
                            return -1;
                        }
                        sd.setOffset(sd.getOffset() + section->getOffset());
                        d.insert(sd);
                    }
                } else {
                    // Symbol not defined
                    if(!u.count(sd)) {
                        u.insert(sd);
                    }
                }
            } else {
                // Symbol is local and is not a section symbol
                SectionData* section = i.getSM().getSectionByName(sd.getSection());
                if(!section) {
                    std::cout << RED << "Error while linking the symbol table, missing section: " << sd.getSection() << "!" << NC << std::endl;
                    return -1;
                }
                sd.setOffset(sd.getOffset() + section->getOffset());
                sd.setLinkedIndex(linked.getST().getTable().size());
                
                linked.getST().symbolAdd(sd.getName(), sd.getIsGlobal(), sd.getIsExtern(), sd.getSection(), sd.getHasValue(), sd.getOffset());
            }*/
            
        }
    }

    

    
    SymbolTable& st = linked.getST();
    /*for(SymbolData sd : u) {
        st.symbolAdd(sd.getName(), sd.getIsGlobal(), sd.getIsExtern(), sd.getSection(), sd.getHasValue(), sd.getOffset());
    }
    for(SymbolData sd : d) {
        st.symbolAdd(sd.getName(), sd.getIsGlobal(), sd.getIsExtern(), sd.getSection(), sd.getHasValue(), sd.getOffset());
    }*/

    // Deal with relocation tables
    for(FileInfo& i : files) {
        SectionManager& sm = linked.getSM();
        for(SectionData& sd : i.getSM().getList()) {
            sm.beginSection(sd.getName());
            SectionData& linkedSection = *sm.getCurrent();
            // Append relocation table with increased offset
            for(RelData& rd : sd.getRelTable().getTable()) {
                linkedSection.getRelTable().append(
                    rd.getOffset() + sd.getOffset(), 
                    rd.getType(), 
                    i.getST().getTable()[rd.getSymbID()].getLinkedIndex(), 
                    rd.getAddend());
            }
        }
    }
    
    if(output == ELF) {
        // Linkable output
        std::ofstream of;
		of.open(output_filename);

		if (of.is_open()) { 
			of << std::hex;
			of << linked.getST();
			of << linked.getSM();
			of.flush();
			of.close();
		} else {
			std::cout << RED << "Error cannot open output file!" << NC << std::endl;
            return -1;
		}
    } else {
        // Loadable output
        // Place section with defined positions
        pd.sort();
        int max_pos = 0;
        std::string past_name = "";
        for(PlaceData& i : pd) {
            //Set section positions
            SectionData* sd = linked.getSM().getSectionByName(i.name);
            if(sd) {
                if(i.place < max_pos) {
                    std::cout << RED << "Conficting sections: " << past_name << " " << i.name << NC << std::endl;
                } else {
                    if(sd->getIsPositioned() == true) {
                        std::cout << RED << "Section: " << i.name << " is already positioned!" << NC << std::endl;
                    }
                    sd->setOffset(max_pos);
                    sd->setIsPositioned(true);
                    SymbolData* symbol = linked.getST().getSymbolByName(i.name);
                    if(symbol) {
                        symbol->setOffset(max_pos);
                        symbol->setHasValue(true);
                    }
                    max_pos = max_pos + sd->getData().size();
                    past_name = i.name;
                }
            }
            //std::cout << i.name << " " << i.place << std::endl;
        }
        // Place other sections
        for(SectionData& sd : linked.getSM().getList()) {
            if(sd.getName() != "UND" && sd.getName() != "ABS" && !sd.getIsPositioned()) {
                sd.setOffset(max_pos);
                sd.setIsPositioned(true);
                SymbolData* symbol = linked.getST().getSymbolByName(sd.getName());
                if(symbol) {
                    symbol->setOffset(max_pos);
                    symbol->setHasValue(true);
                }
                max_pos = max_pos + sd.getData().size();
            }
        }

        // Check if all symbols are defined
        for(SymbolData& sd : linked.getST().getTable()) {
            if(!sd.getHasValue()) {
                std::cout << RED << "Symbol " << sd.getName() << " in section " << sd.getSection() << " is not defined, cannot generate hex output!" << NC << std::endl;
                return -1;
            }
        }
        
        std::cout << YEL << "Before relocation" << NC << std::endl;
        std::cout << linked.getST();
        std::cout << linked.getSM();

        // Deal with relocation tables
        for(SectionData& sd : linked.getSM().getList()) {
            for(RelData& rd : sd.getRelTable().getTable()) {
                SymbolData* symbol = &linked.getST().getTable()[rd.getSymbID()];//linked.getST().getSymbolByName(rd.getSymbName());
                if(!symbol) {
                    std::cout << RED << "Missing symbol: " << rd.getSymbID() << " for relocation in section " << sd.getName() << "!" << NC << std::endl;
                    return -1;
                }

                uint16_t temp = 0;

                if(symbol->getName() == symbol->getSection()) {
                    // Symbol is a section name
                    temp = symbol->getOffset() + rd.getAddend();
                    
                } else {
                    SectionData* symbolSection = linked.getSM().getSectionByName(symbol->getSection());
                    if(!symbolSection) {
                        std::cout << RED << "Missing section: " << symbol->getSection() << "!" << NC << std::endl;
                        return -1;
                    }

                    temp = symbol->getOffset() + symbolSection->getOffset() + rd.getAddend();
                }
                

                if(rd.getType() == 4) {
                    // PC points to the next instruction
                    temp -= rd.getOffset() + sd.getOffset() - 3 + rd.getAddend() + rd.getAddend();
                }

                if(rd.getOffset() < 0 || rd.getOffset() > sd.getData().size()) {
                    std::cout << RED << "Relocation in section " << symbol->getSection() << " out of range(" << rd.getOffset() << ")!" << NC << std::endl;
                    return -1;
                }

                sd.getData()[rd.getOffset()] = temp >> 8;
                sd.getData()[rd.getOffset() + 1] = temp & 0xff;
            }
        }
        std::cout << YEL << "After relocation" << NC << std::endl;
        std::cout << linked.getST();
        std::cout << linked.getSM();

        // Print
        std::ofstream of;
		of.open(output_filename);

		if (of.is_open()) { 
			of << std::hex;
			linked.getSM().writeHex(of);
			of.flush();
			of.close();
		} else {
			std::cout << RED << "Error cannot open output file!" << NC << std::endl;
            return -1;
		}
    }
    
}

/*
try{

    } catch (LinkerException* e) {
        std::cout << RED << e->msg << NC << std::endl;
        delete e;
        return -1;
    }
    */