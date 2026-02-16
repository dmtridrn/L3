.globl _start
        
.section .text
_start:
        mov $3, %edi
        imul $5, %edi
        mov $2, %esi
        imul $2, %esi
        add %esi, %edi
        imul %edi, %edi
        call print_int32
        
        mov $0, %edi
        call exit
# code c
int main() {
  int j;
  j = 3 * 5 + 2 * 2;
  print_int32(j * j);
  exit(0);
}
# code a 2 valeurs
j = 3
j *= 5
x = 2
x *= 2
j+=x
j*=j
print(j)
exit
