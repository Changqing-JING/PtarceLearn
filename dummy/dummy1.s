.intel_syntax noprefix

.data
message:  
.ascii "Hello, World\n"   

.text
.globl _start
_start:   
          mov  rax, 1                 
          mov  rdi, 1               
          mov  rsi, offset [message]         
          mov rdx, 13               
          syscall                          
          mov rax, 60                 
          xor rdi, rdi               
          syscall    

  

