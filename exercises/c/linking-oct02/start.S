    .globl _start
    .text
_start:
    call main
    mov %eax, %edi
    mov $60, %eax
    syscall
    .section .note.GNU-stack,"",@progbits
