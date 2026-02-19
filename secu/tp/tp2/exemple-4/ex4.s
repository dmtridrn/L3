        .globl _start
        
        .section        .text
_start:
        # init
        sub $(256*4), %rsp
        mov $2, %r12 # r12 = i = 0
        .L_begin1:
        cmp $256, %r12
        je .L_end1
        movl $1, (%rsp, %r12, 4)
        add $1, %r12
        jmp .L_begin1
        .L_end1:

        # boucle exterieure

        mov $2, %r12
        .L_begin2:
        cmp $256, %r12
        je .L_end2
        cmpl $0, (%rsp, %r12, 4)
        je .L_next_i
        # boucle intérieure
        mov %r12, %rax
        imul %r12, %rax
        mov %rax, %r13 # j = i*i
        .L_begin3:
        cmp $256, %r13
        jge .L_end3
        movl $0, (%rsp, %r13, 4)
        add %r12, %r13
        jmp .L_begin3
        .L_end3:
        # fin boucle exte
        .L_next_i:
        add $1, %r12
        jmp .L_begin2
        .L_end2:

        mov $2, %r12
        .L_begin4:
        cmp $256, %r12
        je .L_end4

        cmpl $0, (%rsp, %r12, 4)
        je .L_next_i2

        mov %r12d, %edi
        call print_int32

        .L_next_i2:
        add $1, %r12
        jmp .L_begin4
        .L_end4:

        add $1024, %rsp
        mov $0, %edi
        call exit

# code a deux valeurs:

int n = 256
int tab[n]
int i = 0
begin1
if i = n goto end1
tab[i] = 1
i += 1
goto begin1
end1
tab[0] = 0
tab[1] = 0

i = 2
begin2
if i = n goto end2
if tab[i] = 0 goto after_if
j = i*i
begin3
if j >= n goto after_if
tab[j] = 0
j += i
goto begin3
after_if
i += 1
goto begin2
end2
exit(0)

# code c
int main(){
    int n = 256,
    int tab[n],
    for(int i = 0, i<n, i++){
        tab[i] = 1,
    }
    tab[0] = 0,
    tab[1] = 0,
    for(int i = 2, i<n, i++){
        if(tab[i]){
            for(int j = i*i, j<n, j+=i){
                tab[j] = 0,
            }
        }
    }
    for(int i = 0, i<n, i++){
        if(tab[i]) printf("%d\n", i),
    }
}
