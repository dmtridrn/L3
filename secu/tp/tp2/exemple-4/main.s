        .globl _start
        
        .section        .text
_start:
        sub $(12*4), %rsp
        
        mov $0, %ecx  
        .L_start.loop_1_begin:
        cmp $12, %ecx
        jge .L_start.loop_1_end
        mov %ecx, %edi
        add $1, %edi
        movslq %ecx, %rcx
        mov %edi, (%rsp, %rcx, 4)
        add $1, %ecx
        jmp .L_start.loop_1_begin
        .L_start.loop_1_end:

        mov $1, %ebx
        .L_start.loop_2_begin:
        cmp $12, %ebx
        jge .L_start.loop_2_end
        movslq %ebx, %rbx
        mov (%rsp, %rbx, 4), %edi
        add -4(%rsp, %rbx, 4), %edi
        call print_int32
        add $1, %ebx
        jmp .L_start.loop_2_begin
        .L_start.loop_2_end:

        mov $0, %edi
        call exit
