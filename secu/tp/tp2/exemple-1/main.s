        .globl _start
        
	.section        .text
_start:
        mov $0, %edi
        mov $6, %edi
        imul $7, %edi
        call print_int32
        
        mov $0, %edi
        call exit
