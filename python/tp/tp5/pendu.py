import random as r

PENDU = [
    """
       -----
       |   |
       |
       |
       |
       |
    --------
    """,
    """
       -----
       |   |
       |   O
       |
       |
       |
    --------
    """,
    """
       -----
       |   |
       |   O
       |   |
       |
       |
    --------
    """,
    """
       -----
       |   |
       |   O
       |  /|
       |
       |
    --------
    """,
    """
       -----
       |   |
       |   O
       |  /|\\
       |
       |
    --------
    """,
    """
       -----
       |   |
       |   O
       |  /|\\
       |  / \\
       |
    --------
    """,
]

def affiche_pendu(essais: int):
    print(PENDU[5 - essais])

def choisir_mot(nomfich: str):
    with open(nomfich, 'r') as f:
        l = f.readlines()
    mot = l[r.randint(0, len(l)-1)]
    return mot.strip()

def jouer_tour(mot: str, l: list, essais: int):
    if essais == 0:
        print("HAHAHAHAHAHAHAHHAHAHA PERDUUUUUU LOOOOOOOOSEEEEEEER")
        return essais
    print("-------proposez une lettre ou un mot-------\n")
    prop = input()
    if prop == mot:
        print("GAGNÉ BRAVOOOOOOO\n")
        return 0
    else:
        if prop not in mot:
            essais -= 1
            affiche_pendu(essais)
            print(f"-------plus que {essais} essais-------\n")
            return essais
        for i in range(0, len(mot)):
            if mot[i] == prop:
                l[i] = prop
    return essais


def affiche_liste(liste):
    for i in liste:
        print(i, end=" ")
    print("\n")


mot = choisir_mot("dico_pendu.txt")
essais = 5
liste = [" _ "]*len(mot)
affiche_pendu(essais)
affiche_liste(liste)
while(essais > 0):
    essais = jouer_tour(mot, liste, essais)
    affiche_liste(liste)
print(f"-------le mot était \'{mot}\'-------")