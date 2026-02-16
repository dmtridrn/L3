Le programme contenu dans le fichier `main.s` affiche les entiers de 1 à 12.

Le code à deux valeurs avec branchements correspondant est le suivant :

```
int i;
i = 1;
loop_1_begin:
if (i > 12) goto loop_1_end;
print_int32(i);
i += 1;
goto loop_1_begin;
loop_1_end:
exit(0);
```

Le code C correspondant est le suivant :

```
int main() {
  for (int i = 1; i <= 12; i++) {
    print_int32(i);
  }
  exit(0);
}
```
