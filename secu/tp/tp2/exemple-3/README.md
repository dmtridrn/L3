Le programme contenu dans le fichier `main.s` affiche les entiers impairs de 3 à
23 utilisant un tableau *global* stocké dans la section `.data` (qui fait partie
d'un segment de mémoire accessible en écriture, contrairement au code du
programme).

L'instruction `mov %edi, my_array( , %ecx, 4)` signifie « écrire la valeur de
`%edi` dans la mémoire à l'adresse `my_array + %ecx * 4` ».

L'instruction `add my_array-4( , %ebx, 4), %edi` signifie « ajouter à `%edi`
la valeur stockée en mémoire à l'adresse `my_array - 4 + %ebx * 4` ».

Le code à deux valeurs avec branchements correspondant est le suivant :

```
int i, j, my_array[12];

i = 0;
loop_1_begin:
if (i >= 12) goto loop_1_end;
j = i;
j += 1;
my_array[i] = j;
i += 1;
goto loop_1_begin;
loop_1_end:

i = 1;
loop_2_begin:
if (i >= 12) goto loop_2_end;
j = my_array[i];
j += my_array[i-1];
print_int32(i);
i += 1;
goto loop_2_begin;
loop_2_end:

exit(0);
```

Le code C correspondant est le suivant :

```
int my_array[12];

int main() {
  for (int i = 0; i < 12; i++) {
    my_array[i] = i+1;
  }
  for (int i = 1; i < 12; i++) {
    print_int32(my_array[i-1] + my_array[i]);
  }
  exit(0);
}
```
