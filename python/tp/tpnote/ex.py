import re


def Chaine(s:str):
    return s.isdigit()

def aux(L):
    return [i for i in L if i%2 == 0]

def zzz(l1,l2):
    res = []
    for i in range(len(l1)):
        res.append(l1[i])
        res.append(l2[i])
    return res

def TriAbsDecr(l: list):
    l.sort(key=lambda x: abs(x), reverse=True)
    return l

def verifDico(d:dict):
    return len(d.keys()) != len(set(d.values()))


def nbLignes(nom:str):
    with open(nom, 'r') as f:
        lignes = f.readlines()
        for l in lignes:
            if "bip" in l:
                print(l)

