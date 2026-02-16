L'objectif de ce TP est de vous initier à la programmation en assembleur x86-64.

Pour chacun des exercices 1 à 3, on vous fournit un répertoire contenant un
exemple de programme et des informations complémentaires. Il est recommandé de
procéder dans l'ordre suivant :

1. Lire en entier le sujet de l'exercice `N` ;

2. Lire les fichiers `exemple-N/README.md` et `exemple-N/main.s` et tester le
   programme d'exemple ;

3. Répondre aux questions de l'exercice `N`.


Exercice 1
==========

On considère le programme C suivant :

```
int main() {
  int j;
  j = 3 * 5 + 2 * 2;
  print_int32(j * j);
  exit(0);
}
```

1. Convertissez ce programme en *code à 2 valeurs*, c'est-à-dire où toute
   instruction a l'une des formes suivantes :
   
   * x = y (où x est une variable et y est une variable ou une constante) ;
   
   * x OP= y (où OP est un opérateur binaire comme +, - ou * ; x est une
     variable ; et y est une variable ou une constante) ;
     
   * f(y) (où f est une fonction et y est une variable ou une constante).
   
   Vous aurez probablement besoin d'introduire de nouvelles variables.
   
2. Affectez à chacune des variables de ce code à deux valeurs un registre
   général x86-64 (autre que `%rsp`).

3. Convertissez ce code à deux valeurs en assembleur x86-64, puis assemblez-le
   et testez-le (en prenant comme base le contenu du répertoire `exemple-1`).
   
   Pour appeler la fonction `print_int32(int n)`, il faut placer son argument
   dans le registre `%edi` puis utiliser l'instruction `call print_int32`.


Exercice 2
==========

En C, l'instruction `goto my_label` effectue un *branchement* vers la ligne de
code désignée par l'*étiquette* `my_label`. Par exemple, le code suivant affiche
seulement « Leonardo » et « Michelangelo » :

```
ìnt main() {
  puts("Leonardo");
  goto oubli;
  puts("Donatello");
  puts("Raphael");
  oubli:
  puts("Michelangelo");
  exit(0);
}
```

On appelle *branchement conditionnel* toute instruction de la forme 
`if (condition) goto my_label;` (sans « else »).

On considère le programme C suivant :

```
int main() {
  int i, j;
  for(i = 0; i < 10; i++) {
    j = 3 * i + 2;
    print_int32(j * j);
  }
  exit(0);
}
```

1. Réécrivez ce programme en remplaçant toutes les structures de contrôle
   (`for`, `while`, `if`, etc.) par des combinaisons de branchements
   inconditionnels et de branchements conditionnels.

2. Convertissez le programme ainsi obtenu en *code à deux valeurs avec
   branchements*, c'est-à-dire où toute instruction a l'une des formes
   suivantes :
   
   * une instruction en code à deux valeurs ;
   
   * un branchement inconditionnel ;
   
   * un branchement conditionnel de la forme `if (x CMP y) goto my_label`,
     où `x` et `y` sont des variables ou des constantes et `CMP` est un
     opérateur de comparaison.

3. Convertissez ce code à deux valeurs avec branchements en assembleur x86-64,
   puis assemblez-le et testez-le.
   
   En assembleur, x86-64 l'instruction `jmp my_label` effectue un branchement
   inconditionnel vers l'instruction désignée par l'étiquette `my_label`.
   
   La séquence d'instructions suivante effectue un branchement si et seulement
   si la valeur de `%eax` (vue comme un entier signé) est strictement plus
   petite que celle de `%edx` (également vue comme un entier signé) :
   
   ```
   cmp %edx, %eax
   jl my_label
   ```
   
   Le code d'opération `jl` signifie « jump if less than ». Il existe également :
   
   * `jg` : jump if greater ;
   
   * `je` : jump if equal ;
   
   * `jle` : jump if less or equal ;
   
   * `jge` : jump if greater or equal.


Exercice 3
==========

On considère le programme C suivant :

```
int a[16];

int main()
{
  int i, j;
  a[0] = 0;
  a[1] = 1;
  for(i = 2; i < 16; i++) {
    a[i] = a[i - 2] + a[i - 1];
  }
  for(j = 15; j >= 0; j--) {
    print_int32(a[j]);
  }
  exit(0);
}
```

1. Convertissez-le en code à deux valeurs avec branchements. Vous pouvez
   utiliser les cases du tableau comme des variables avec la restriction
   suivante : vous ne pouvez pas accéder à deux cases dans la même
   instruction. Par exemple, l'instruction `a[i] = a[j]` n'est pas permise.

2. Convertissez-le en assembleur x86-64 en plaçant le tableau `a` dans la
   section `.data`, puis assemblez-le et testez-le.

3. En vous inspirant du fichier `exemple-4/main.s`, modifiez le code assembleur
   de la question précédente pour que le tableau `a` soit alloué sur la
   pile.

Exercice 4
==========

1. Écrivez un programme en C qui utilise l'algorithme du *crible d'Ératosthène*
   pour afficher tous les nombres premiers inférieurs à 256.

3. Convertissez-le en code à deux valeurs avec branchements.

2. Convertissez-le en assembleur x86-64, puis assemblez-le et testez-le.
