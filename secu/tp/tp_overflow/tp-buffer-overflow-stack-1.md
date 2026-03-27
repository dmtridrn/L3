# TP Buffer overflow sur la pile n°1

Téléchargez le fichier `si6-tp-buffer-overflow-stack-1.tar.gz`. Détarrez-le
depuis la ligne de commande.

## Buffer overflow

Dans le répertoire `jeden`, vous trouverez un programme binaire `jeden` et
le programme source corresondant.  Écrivez un fichier `jeden.in` tel qu'un
appel à `./jeden < jeden.in` affiche « Douze vaut 42. ».  Vous n'êtes pas
autorisés à modifier le binaire, et vous n'êtes pas autorisés à recompiler
le programme.

```C
#include <stdio.h>

int main() {
    volatile int i = 12;
    char s[32];
    
    printf("Entrez votre nom:\n");
    scanf("%s", s);
    printf("Douze vaut %d.\n", i);
    return 0;
}
```

## Buffer overflow 2

Dans le répertoire `dwa`, vous trouverez un programme binaire `dwa`.
Cette fois-ci, nous ne vous donnons pas le code source, mais nous vous
indiquons qu'il a exactement la même structure que le programme de
l'exercice précédent.

Donnez un fichier `dwa.in` tel qu'une exécution de `./dwa < dwa.in`
affiche le nom de la fille de Minos et de Pasiphaé.

## Bornes de tableaux

Dans le fichier `~geoffroy/public/si6/trzy`, vous trouverez un programme
exécutable qui a été compilé à partir du code suivant, mais où la chaîne
`SECRET` a été remplacée par un secret que vous ne connaissez pas (sinon,
ce ne serait pas un secret).  Déterminez le secret (qui, du coup, ne sera
plus un secret).

```C
#include <stdio.h>

char *mot_de_passe = "SECRET";

char *nombres = {
    "zero", "jeden", "dwa", "trzy", "cztery", "pięć", 
}

int main() {
    int i;
    printf("Entrez un nombre.\n");
    scanf("%d", i);
    printf("%s\n", nombres[i]);
    return 0;
}
```

## Corruption de l'adresse de retour

Le fichier `~geoffroy/public/si6/cztery` a été compilé à partir du code
source ci-dessous.

```C
#include <stdio.h>

void print_password(void) {
    printf("%s\n", "SECRET");
}

void read_name() {
    char buf[32];
    scanf("%s", buf);
}

int main() {
    read_name();
    return 0;
}
```

Compilez le programme à l'aide de `gcc -g`, puis ouvrez-le dans `gdb`.

1. Quelle est l'adresse de l'instruction qui suit l'appel à `read_name` ?

2. Insérez un *breakpoint* sur l'appel à `scanf`.  À quel déplacement
   depuis `rsp` se trouve le tampon ?  À quel déplacement se trouve
   l'adresse de retour ?
   
3. En utilisant la version présente sur lulu, déterminez le secret.
