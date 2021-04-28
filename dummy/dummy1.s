

.data
message:  
.ascii "Hello, World\n"   

.text
.globl _start
_start:   
          movq $1, %rax                  
          movq  $1, %rdi                
          movq  $message, %rsi            
          movq  $13, %rdx               
          syscall                          
          movq  $60, %rax                 
          xorq %rdi, %rdi               
          syscall    

  

