.globl _start
        
.section .text
_start:
        mov $0, %ebx        
        .L_start.loop_1_begin:
        cmp $10, %ebx
        je .L_start.loop_1_end
        mov %ebx, %edi
        imul $3, %edi
        add $2, %edi
        imul %edi, %edi
        call print_int32
        add $1, %ebx
        jmp .L_start.loop_1_begin
        .L_start.loop_1_end:
        
        mov $0, %edi
        call exit



# code c
int main() {
  int i, j;
  for(i = 0, i < 10, i++) {
    j = 3 * i + 2;
    print_int32(j * j);
  }
  exit(0);
}

# deux val
i = 0
j = 0
deb
if i = 10 goto end
j = i
j *= 3
j += 2
j*=j
print(j)
i+=1
goto deb
end
exit