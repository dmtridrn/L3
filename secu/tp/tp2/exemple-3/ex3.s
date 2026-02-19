        .globl _start

        .section        .text
_start:        
        sub $(16*4), %rsp
        mov $2, %r12 #  r12 = i
        mov $15, %r13 #  r13 = j
        movl $1, 4(%rsp) # array[1] = 1

        .L_start.loop_1_begin:
        cmp $16, %r12
        je .L_start.loop_1_end
        mov -8(%rsp, %r12, 4), %edi # edi = x
        mov -4(%rsp, %r12, 4), %ecx #  ecx = y
        add %edi, %ecx
        mov %ecx, (%rsp, %r12, 4)
        add $1, %r12
        jmp .L_start.loop_1_begin
        .L_start.loop_1_end:

        .L_start.loop_2_begin:
        cmp $0, %r13
        jl .L_start.loop_2_end
        mov (%rsp, %r13, 4), %ebx
        mov %ebx, %edi
        call print_int32
        sub $1, %r13
        jmp .L_start.loop_2_begin
        .L_start.loop_2_end:  

        add $(16*4), %rsp
        mov $0, %edi
        call exit

; deux valeurs:

int a[16]
int i = 2
int j = 15

a[0] = 0
a[1] = 1

begin1
if i = 16 goto end1
int x = a[i-2]
int y = a[i-1]
y = x + y
a[i] = z
i += 1
goto begin1
end1

begin2
if j < 0 goto end2
int k = a[j]
print(k)
j -= 1
goto begin2
end2
exit(0)

; c

int a[16];

int main()
{
  int i, j
  a[0] = 0
  a[1] = 1
  for(i = 2, i < 16, i++) {
    a[i] = a[i - 2] + a[i - 1];
  }
  for(j = 15, j >= 0, j--) {
    print_int32(a[j]);
  }
  exit(0);
}