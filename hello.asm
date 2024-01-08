section .data
    hello db 'Hello, World!\n',0 ; null-terminated string to be printed

section .text
    global _start             ; must be declared for linker (ld)

_start:                       ; tell linker entry point
    mov eax,4                ; system call number (sys_write)
    mov ebx,1                ; file descriptor (stdout)
    mov ecx,hello            ; pointer to message to write
    mov edx,13               ; message length
    int 0x80                 ; call kernel

    mov eax,1                ; system call number (sys_exit)
    xor ebx,ebx              ; exit code
    int 0x80                 ; call kernel