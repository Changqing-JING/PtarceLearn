#include "ptrace_common.h"

int test_PTRACE_SINGLESTEP(){
    pid_t child;
    const int long_size = sizeof(long);
    child = fork();
    if(child == 0) {
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        execl("./build/dummy/dummy1", "dummy1", NULL);
    }
    else {
        int status;
        union u {
            long val;
            char chars[long_size];
        }data;
        struct user_regs_struct regs;
        int start = 0;
        long ins;
        
        while(1) {
            wait(&status);
            if(WIFEXITED(status)){
                break;
            }
                
            ptrace(PTRACE_GETREGS,
                   child, NULL, &regs);
            ins = ptrace(PTRACE_PEEKTEXT, child, regs.rip, NULL);
            printf("EIP: %llx Instruction executed: %lx\n", regs.rip, ins);
            printf("rax:%llx, rdi:%llx, rsi:%llx, rdx: %llx\n", regs.rax, regs.rdi, regs.rsi, regs.rdx);
            printf("-------------------------------------\n");
            ptrace(PTRACE_SINGLESTEP, child, NULL, NULL);

            
           
                
        }
    }
    return 0;
}