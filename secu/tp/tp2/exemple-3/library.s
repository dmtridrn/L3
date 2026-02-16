	.text
	.globl exit, print_int32, print_int64

exit:
# Argument dans %edi
        mov $60, %rax
        syscall
        
print_int32:
# Argument dans %edi
        push %rdi
        movslq %edi, %rdi
        call print_int64
        pop %rdi
        ret

print_int64:
# Argument dans %rdi
        push %rax
        push %rdi
        push %rsi
        push %rdx
        push %rcx
        sub $24, %rsp

        mov $23, %rcx
        movb $'\n', (%rsp, %rcx)

        mov %rdi, %rax
        cmp $0, %rax
        jge 1f
        neg %rax
        1:

        1:
        test %rax, %rax
        jz 2f
        mov $0, %rdx
        mov $10, %rsi
        div %rsi
                                # %rax <- %rdx:%rax / %rsi (quotient)
                                # %rdx <- %rdx:%rax % %rsi (reste)
        add $'0', %dl
        sub $1, %rcx
        mov %dl, (%rsp, %rcx)
        jmp 1b
        2:

        test %rdi, %rdi
        jnz 1f
        sub $1, %rcx
        movb $'0', (%rsp, %rcx)
        1:

        cmp $0, %rdi
        jge 1f
        sub $1, %rcx
        movb $'-', (%rsp, %rcx)
        1:

        mov $1, %rax
        mov $1, %rdi
        mov %rsp, %rsi
        add %rcx, %rsi
        mov $24, %rdx
        sub %rcx, %rdx
        syscall

        add $24, %rsp
        pop %rcx
        pop %rdx
        pop %rsi
        pop %rdi
        pop %rax
        ret

        
