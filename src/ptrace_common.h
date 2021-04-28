#ifndef _PTRACE_COMMON_

#define _PTRACE_COMMON_


#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/user.h> 
#include <stdio.h>
#include <sys/reg.h>
#include <sys/syscall.h>

#define RegisterSize sizeof(void*)

#endif