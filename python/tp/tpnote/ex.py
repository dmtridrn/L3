def Chaine(s: str):
    return s.isdigit()

def aux(L):
    return [i for i in L if i%2 == 0]

def sous_liste(L, k1, k2):
    return [i for i in L if (i<=k2) and (i>=k1)]

def zzz(L1,L2):
    x = []
    for i in range(0,len(L1)):
        x.append(L1[i])
        x.append(L2[i])
    return x

def TriAbsDecr(L):
    return sorted(L, key=abs, reverse=True)
