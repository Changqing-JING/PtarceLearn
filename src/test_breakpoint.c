#include "test_breakpoint.h"
#include "ptrace_common.h"
#include "string.h"
#include "stdlib.h"
#include "stdint.h"

static const unsigned char INT3 = 0xCC;

const int long_size = sizeof(long);


static void printRegisters(pid_t child){
    struct user_regs_struct regs;
    ptrace(PTRACE_GETREGS,child, NULL, &regs);
    long ins = ptrace(PTRACE_PEEKTEXT, child, regs.rip, NULL);
    printf("EIP: %llx Instruction executed: %lx\n", regs.rip, ins);
    printf("rax:%llx, rdi:%llx, rsi:%llx, rdx: %llx\n", regs.rax, regs.rdi, regs.rsi, regs.rdx);
    printf("-------------------------------------\n");
}

int test_breakpoint()
{   
    pid_t child;
    const int long_size = sizeof(long);
    child = fork();
    if(child == 0) {
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        printf("start debug\n");
        execl("./build/dummy/dummy1", "dummy1", NULL);
    }
    else {
        int status;      

        wait(&status);
        uintptr_t addr =  0x000000000040101c;

        long ins = ptrace(PTRACE_PEEKDATA, child, addr, NULL); //save instruction

        
        ptrace(PTRACE_POKEDATA, child, addr, INT3);    //write int3 at the address
        
        ptrace(PTRACE_CONT, child, NULL, NULL); //continue

        wait(0);
        printRegisters(child); //SIGCHLD received by int3

        ptrace(PTRACE_POKEDATA, child, addr, ins);    //recover instruction

        long rip = ptrace(PTRACE_PEEKUSER, child, RegisterSize * RIP, NULL);

        ptrace(PTRACE_POKEUSER, child, RegisterSize * RIP, rip-1);

        ptrace(PTRACE_CONT, child, NULL, NULL); //continue
                
        
    }
    return 0;
}