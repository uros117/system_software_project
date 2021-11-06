#include "Call.hpp"
#include "Argument.hpp"
#include "util.hpp"
#include "SectionManager.hpp"
#include "AssemblerException.hpp"

Call::Call(unsigned int number, Argument* a1) : Instr(number, 3, "call", a1, nullptr) {
    this->setSize(a1->instrLength());
}

void Call::pass1() {

}

void Call::pass2() {
    SectionManager& sm = SectionManager::getInstance();
    SectionData* sd = sm.getCurrent();
    sd->appendData(0b00110000);
    unsigned char c = 0b11110000;
    unsigned char m = 0b00001111;
    uint16_t temp = (uint16_t)getA1()->getLiteral();
    unsigned char tl = ((unsigned char*)&temp)[0];
    unsigned char th = ((unsigned char*)&temp)[1];
    switch(getA1()->getType()) {
        case 0:
            // <literal>
            sd->appendData(c);
            sd->appendData(UPDATE_NONE | ADDR_MODE_IMMED);
            sd->appendData(th);
            sd->appendData(tl);
            break;
        case 1:
            // <symbol>
            sd->getRelTable().append(sd->getLocationCounter() + 3, 1, getA1()->getSymbol(), 0);
            sd->appendData(c);
            sd->appendData(UPDATE_NONE | ADDR_MODE_IMMED);
            sd->appendData(0);
            sd->appendData(0);
            break;
        case 4:
            // %<symbol>
            sd->getRelTable().append(sd->getLocationCounter() + 3, 4, getA1()->getSymbol(), 5);
            sd->appendData(0b11110111);
            sd->appendData(UPDATE_NONE | ADDR_MODE_REGDIR_PAYLOAD);
            sd->appendData(0);
            sd->appendData(0);
            break;
        case 9:
            // *<literal>
            sd->appendData(c);
            sd->appendData(UPDATE_NONE | ADDR_MODE_MEM);
            sd->appendData(th);
            sd->appendData(tl);
            break;
        case 10:
            // *<symbol>
            sd->getRelTable().append(sd->getLocationCounter() + 3, 10, getA1()->getSymbol(), 0);
            sd->appendData(c);
            sd->appendData(UPDATE_NONE | ADDR_MODE_MEM);
            sd->appendData(0);
            sd->appendData(0);
            break;
        case 11:
            // *<reg>
            sd->appendData(c | (m & getA1()->getRegNum()));
            sd->appendData(UPDATE_NONE | ADDR_MODE_REGDIR);
            break;
        case 12:
            // *[<reg>]
            sd->appendData(c | (m & getA1()->getRegNum()));
            sd->appendData(UPDATE_NONE | ADDR_MODE_REGINDIR);
            break;
        case 13:
            // *[<reg> + <literal>]
            sd->appendData(c | (m & getA1()->getRegNum()));
            sd->appendData(UPDATE_NONE | ADDR_MODE_REGINDIR_PAYLOAD);
            sd->appendData(th);
            sd->appendData(tl);
            break;
        case 14:
            // *[<reg> + <symbol>]
            sd->getRelTable().append(sd->getLocationCounter() + 3, 14, getA1()->getSymbol(), 0);
            sd->appendData(c | (m & getA1()->getRegNum()));
            sd->appendData(UPDATE_NONE | ADDR_MODE_REGINDIR_PAYLOAD);
            sd->appendData(0);
            sd->appendData(0);
            break;
            
        default:
            throw new AssemblerException("Invalid address mode!");
            break;
    }
}

Call::~Call() {

}
