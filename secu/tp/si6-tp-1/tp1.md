Installation d'opam, OCaml et dune
==================================

Installez d'abord opam, le gestionnaire de paquets pour OCaml. L'idéal est
d'utiliser le gestionnaire de paquets de votre distribution. Sous Ubuntu par
exemple :

```
# apt install opam
```

Vous devez ensuite initialiser opam. On vous proposera de modifier
automatiquement un fichier (probablement `~/.profile`) : acceptez en tapant `y`.

```
$ opam init ; eval $(opam env)
```

Vous pouvez maintenant installer OCaml à l'aide d'opam. Cette étape n'est pas
indispensable si vous l'aviez déjà installé à l'aide du gestionnaire de paquets de
votre distribution.

```
$ opam switch create "ocaml.5" --formula '"ocaml" { >= "5" & < "6" }'
```

Enfin, installez `dune`, le « build system » d'OCaml :
```
$ opam install dune
```


Exemples de programmes
======================

Les dossiers `hello-world` et `cat` contiennent deux exemples de programmes
écrits en OCaml.


Le programme hello-world
------------------------

Son code source est contenu dans le fichier `bin/helloWorld.ml`. Vous pouvez le
compiler en lançant la commande `dune build` depuis la racine du projet
(c'est-à-dire depuis le répertoire `hello-world`). Vous pouvez l'exécuter en
lançant la commande `dune exec -- hello-world` ; il sera alors automatiquement
(re)compilé si nécessaire.


Le programme cat
----------------

Il se comporte exactement comme l'utilitaire unix `cat` appelé sans
arguments. Son code source est contenu dans le fichier `bin/cat.ml`. Vous pouvez
l'exécuter en lançant la commande `dune exec -- cat`. Pour rappel, la combinaison
de touches Contrôle+D provoque une condition de fin de fichier sur le côté
"entrée" du terminal.


Exercice 1 : chiffrement de César avec des octets
=================================================

Vous devez écrire un programme `caesar` qui calcule une variante « octet par
octet » du chiffrement de César : la clé est composée d'un octet, qui est
simplement ajouté (pour l'encodage) ou soustraite (pour le décodége) à chaque
octet de l'entrée :

```
$ printf "Bonjour" | dune exec -- caesar -e $(printf "\001")
Cpokpvs
$ printf "Cpokpvs" | dune exec -- caesar -d $(printf "\001")
Bonjour
```

On vous a fourni un fichier source `bin/caesar.ml` qui, dans son état actuel,
interprète les arguments reçus sur la ligne de commande afin de renseigner les
variables `decode : bool` et `key : char` mais n'en tient pas compte au moment
du parcours de l'entrée : il se comporte donc en pratique comme `cat`. À vous de
le modifier pour obtenir le comportement souhaité.

En OCaml, un octet est représenté par une valeur de type `char`. On vous a
fourni un module `Byte`, dont le code source est contenu dans le fichier
`lib/byte.ml` et dont l'interface est définie par le fichier `lib/byte.mli`, qui
permet de manipuler des octets. Vous avez donc accès, entre autres, aux
fonctions suivantes :

 * `Byte.add : char -> char -> char`
 * `Byte.sub : char -> char -> char`
 * `Byte.xor : char -> char -> char`
 * `Byte.of_int : int -> char`
 * `Byte.to_int : char -> int`
 
 Par ailleurs, en OCaml, une séquence d'octets modifiable mais de taille fixée
 est représentée par une valeur du type `bytes`. Le module `Bytes` de la
 bibliothèque standard fournit entre autres les fonctions suivantes :

 * `Bytes.get : bytes -> int -> char`
 * `Bytes.set : bytes -> int -> char -> unit`
 
Quand vous serez satisfait de votre programme et l'aurez testé à la main sur
quelques exemples, vérifiez-le en lançant la commande `dune test`.



Exercice 2 : chiffrement par flot RC4
=====================================

Le principe du chiffrement par flot RC4 est le suivant : à partir de la clé, on
génère un flot infini d'octets. L'octet numéro `n` du message en clair est
combiné avec l'octet uméro `n` du flot par un opération « xor » pour former
l'octet numéro `n` du message chiffré.

Notez que ce système a été abandonné car il ne présente plus des garanties de
sécurités jugées suffisantes.

Vous devez écrire un programme `rc4enc` qui effectue ce chiffrement :

```
$ printf "Plaintext" | dune exec rc4enc "Key" | hexdump -C
00000000  bb f3 16 e8 d9 40 af 0a  d3                       |??.??@?.?|
```

Question : pourquoi ne vous demande-t-on pas d'écrire un programme de
déchiffrement ?

On vous a fourni un fichier source `bin/rc4enc.ml` qui dans son état actuel se
comporte comme `cat` : à vous de le compléter. 

En plus du module `Byte`, on vous a fourni un module `RC4` qui s'occupe de
calculer le flot à partir d'une clé. Il contient notamment :

 * un type abstrait `RC4.t` qui représente un flot ;
 * une fonction `RC4.init : string -> RC4.t` qui crée un flot à partir d'une
   clé ;
 * une fonction `RC4.next : RC4.t -> char` qui renvoie la valeur suivante d'un
   flot :


```
# let sequence = RC4.init "Key";;
val sequence : RC4.t = <abstr>

# RC4.next sequence;;
- : char = '\235'      (* 0xEB *)

# RC4.next sequence;;
- : char = '\159'      (* 0x9f *)

# RC4.next sequence;;
- : char = 'w'         (* 0x77 *)

# RC4.next sequence;;
- : char = '\129'      (* 0x81 *)
```

Quand vous serez satisfait de votre programme et l'aurez testé à la main sur
l'exemple fourni plus haut, vérifiez-le en lançant la commande `dune test`.


Exercice 3 : confidentialité n'implique pas intégrité
=====================================================

Le fichier `badauth.bin` fait 73 octets et contient un ordre de virement que
vous avez intercepté. Il a été obtenu par l'application du chiffrement RC4 à un
fichier au format suivant :

 * un code secret sur 8 octets censé garantir l'identité de l'émetteur
 * suivi du message sur 65 octets :
   "Veuillez virer la somme de 100 dollars a Sir Austin Danger Powers"

À sa réception, le fichier sera déchiffré avec la même clé, et si le code secret
correspond, l'ordre qu'il conient sera exécuté. Vous ne connaissez ni la clé ni
le code secret : modifiez le fichier pour qu'il soit toujours reconnu comme
authentique, mais contienne désormais le message sur 54 octets :
  "Veuillez virer la somme de 1.000.000 dollars a Dr Evil"
  
Le nouveau fichier doit donc faire 62 octets. Si vous pensez avoir réussi,
vérifiez son hash md5, qui doit être le suivant :

```
$ md5sum badauth.evil.bin 
30c113eb0f7403170863d5eae3f25445  badauth.evil.bin
```


Exercice 4 : RC4 et réutilisation de clé
========================================

Le fichier `flow-reuse-ciphertexts.ml` contient un liste de message qui ont tous
été chiffrés avec RC4 en utilisant à chaque fois la même clé. Vous ne connaissez
pas la clé et vous ne savez rien sur les messages d'origine à part qu'ils
consistent chacun en un fragment de texte écrit en français, entièrement en
majuscules et sans aucun accent ni aucune ponctuation à part des
espaces. Autrement dit, le texte d'origine est constitué uniquement des
caractères ASCII 'A' à 'Z' et ' '. Décryptez quelques-uns de ces messages.

Indice : observez bien la représentation binaire des caractères 'A' à 'Z' et
celle du caractère ' '.
