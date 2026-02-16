Le programme contenu dans le fichier `main.s` affiche les entiers impairs de 3 à
23 en utilisant un tableau *local* stocké sur la pile.

L'instruction `sub $(12*4), %rsp` alloue 48 octets sur la *pile*, soit la taille
d'un tableau de 12 entiers. La plage nouvellement allouée est située entre les
adresses `%rsp` (incluse) et `%rsp + 48` (exclue). Le programme devrait en temps
normal remettre la pile dans son état d'origine (et donc libérer cette mémoire
allouée) à l'aide d'une instruction comme `sub $(12*4), %rsp`. Ici, ce n'est pas
nécessaire car le programme termine immédiatement en appelant `exit()`.

L'instruction `movslq %ecx, %rcx` lit la valeur sur 32 bits (`l`) de `%ecx`,
l'interprète comme un entier signé (`s`) et écrit cet entier sur 64 bits (`q`)
dans `%rcx`. Cette opération est nécessaire car l'instruction suivante utilise
`%rcx` au lieu de `%ecx`.

L'instruction `mov %edi, (%rsp, %rcx, 4)` signifie « écrire la valeur de
`%edi` dans la mémoire à l'adresse `%rsp + %rcx * 4` ».

L'instruction `add -4(%rsp, %rbx, 4), %edi` signifie « ajouter à `%edi` la
valeur stockée en mémoire à l'adresse `-4 + %rsp + %rbx * 4` ».

Le code à deux valeurs avec branchements est le même que dans l'exemple 3.

Le code C correspondant est le suivant :

```
int main() {
  int my_array[12];
  for (int i = 0; i < 12; i++) {
    my_array[i] = i+1;
  }
  for (int i = 1; i < 12; i++) {
    print_int32(my_array[i-1] + my_array[i]);
  }
  exit(0);
}
```
