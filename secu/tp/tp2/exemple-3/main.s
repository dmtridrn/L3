        .globl _start
        
        .section        .data
        .align 4
# 12 entiers sur 4 octets chacun, tous égaux à 0
my_array:      .fill 12, 4, 0

        .section        .text
_start:        
        mov $0, %ecx  
        .L_start.loop_1_begin:
        cmp $12, %ecx
        jge .L_start.loop_1_end
        mov %ecx, %edi
        add $1, %edi
        mov %edi, my_array( , %ecx, 4)
        add $1, %ecx
        jmp .L_start.loop_1_begin
        .L_start.loop_1_end:

        mov $1, %ebx
        .L_start.loop_2_begin:
        cmp $12, %ebx
        jge .L_start.loop_2_end
        mov my_array( , %ebx, 4), %edi
        add my_array-4( , %ebx, 4), %edi
        call print_int32
        add $1, %ebx
        jmp .L_start.loop_2_begin
        .L_start.loop_2_end:

        mov $0, %edi
        call exit
