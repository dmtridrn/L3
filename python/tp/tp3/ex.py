def same_elements(l1,l2) -> bool:
    return set(l1) == set(l2)

def letters():
    return {x for x in input("écris phrase:  ").lower() if x.islower()}

def to_liste(s):
    return sorted(s)

def even(s):
    return {x for x in s if x%2 == 0}

def list_to_dic(l: list):
    return dict(enumerate(l))

def charx(w: str):
    return {x:(w.count(x)) for x in set(w)}

def merge(d1: dict, d2: dict):
    return {k:(d1.get(k), d2.get(k)) for k in set(d1)&set(d2)}

def inverse(d: dict):
    return {} if (len(set(d.values())) != len(d.values())) else {v:k for k,v in d.items()}


def print_dict(d: dict):
    for k,v in d.items():
        print(f"{k} {v}")


def Graphe(S, L):
    dico = {x:set() for x in S}
    for x,y in L:
        dico[x].add(y)
    return dico

def PrintG(D: dict):
    for sommet,voisins in D.items():
        voisins2 = ", ".join(voisins)
        print(f"{sommet} -> {voisins2}")


def DFS(g: dict):
    compteur = 0
    pre = {sommet:0 for sommet in g}
    post = {sommet:0 for sommet in g}
    marquage = {sommet:False for sommet in g}

    def parcours(sommet):
        nonlocal compteur
        marquage[sommet] = True
        pre[sommet] = compteur
        compteur += 1
        for voisins in g[sommet]:
            if not marquage[voisins]:
                parcours(voisins)
        post[sommet] = compteur
        compteur += 1
    
    for s in g:
        if not marquage[s]:
            parcours(s)

    return pre, post


