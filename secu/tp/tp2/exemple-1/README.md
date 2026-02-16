Le programme contenu dans le fichier `main.s` affiche l'entier 42. Vous pouvez
l'assembler en lançant la commande `make`, puis l'exécuter en lançant la
commande `./program`.

Le code à deux valeurs correspondant est le suivant :

```
int j;
j = 0;
j += 6;
j *= 7;
print_int32(j);
exit(0);
```

Le code C correspondant est le suivant :

```
int main() {
  int j;
  print_int32((0 + 6) * 7);
  exit(0);
}
```
