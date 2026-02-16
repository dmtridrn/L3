.globl _start
        
.section .text
_start:
        mov $1, %ebx        
        .L_start.loop_1_begin:
        cmp $12, %ebx
        jg .L_start.loop_1_end
        mov %ebx, %edi
        call print_int32
        add $1, %ebx
        jmp .L_start.loop_1_begin
        .L_start.loop_1_end:
        
        mov $0, %edi
        call exit
