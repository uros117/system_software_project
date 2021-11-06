#ifndef __MAIN_H__
#define __MAIN_H__

#define RED "\033[0;31m"
#define YEL "\033[1;33m"
#define NC "\033[0m"

// Memory
extern unsigned char* mem;
// Registers
extern unsigned int r[8];

#define REG_HIGH(reg)               (reg >> 8)
#define REG_LOW(reg)                (reg & 0xff)

#define PC (r[7])
#define SP (r[6])
// r7 - pc
// r6 - sp - used location - grows towards smaller addresses
extern unsigned int psw;
#define PSW                         (psw)
#define PSW_READ(pos)               (psw & 1 << pos)
#define PSW_WRITE(pos, val)         (psw = (psw & ~(1 << pos)) | ((val && 1) << pos))
#define PSW_SET(pos)                (PSW_WRITE(pos, 1))
#define PSW_RESET(pos)              (PSW_WRITE(pos, 0))
#define PSW_I                       (15)
#define PSW_TL                      (14)
#define PSW_TR                      (13)
#define PSW_N                       (3)
#define PSW_C                       (2)
#define PSW_O                       (1)
#define PSW_Z                       (0)


// -15--14--13--12--11--10---9---8---7---6---5---4---3---2---1---0--
// | I |Tl |Tr |   |   |   |   |   |   |   |   |   | N | C | O | Z |
// -----------------------------------------------------------------

// Instruction
extern unsigned char instr[6];
extern unsigned char oc;
#define OC_HALT                     (0x0)
#define OC_INT                      (0x1)
#define OC_IRET                     (0x2)
#define OC_CALL                     (0x3)
#define OC_RET                      (0x4)
#define OC_JUMP                     (0x5)
#define OC_XCHG                     (0x6)
#define OC_ARITM                    (0x7)
#define OC_LOGIC                    (0x8)
#define OC_SHIFT                    (0x9)
#define OC_LOAD                     (0xa) 
#define OC_STORE                    (0xb)
extern unsigned char mod;
extern unsigned char rd;
extern unsigned char rs;
extern unsigned char up;
#define UPDATE_NONE                 (0x0)
#define UPDATE_PRE_DEC              (0x1)
#define UPDATE_PRE_INC              (0x2)
#define UPDATE_POST_DEC             (0x3)
#define UPDATE_POST_INC             (0x4)
extern unsigned char am;
#define ADDR_MODE_IMMED             (0x0)
#define ADDR_MODE_REGDIR            (0x1)
#define ADDR_MODE_REGDIR_PAYLOAD    (0x5)
#define ADDR_MODE_REGINDIR          (0x2)
#define ADDR_MODE_REGINDIR_PAYLOAD  (0x3)
#define ADDR_MODE_MEM               (0x4)

#define INSRT_PAYLOAD               (instr[3] << 8 | instr[4])
// Status
extern int start;

// helper register
extern int rb;
#endif