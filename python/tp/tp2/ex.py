
def ex1(L):
    cpt = 0
    for i in range(1, len(L)-1):
        for j in range(1, len(L[i])-1):
            if L[i][j] > max(L[i+1][j], L[i-1][j], L[i][j+1], L[i][j-1]):
                cpt += 1
    return cpt

def test():
    L=[1,2,3,4]
    L1=L
    L2=L[:]
    L1[1]=18
    L2[1]=20
    print(L)
    print(L1)
    print(L2)

def multiple(n):
    return [i for i in range(0,n) if i%5 == 0 or i%7 == 0]

def multiple_l(l):
    return [i for i in l if i%5 == 0 or i%7 == 0]

def zipping(l, m):
    return [(l[i],m[i]) for i in range(len(l))]

def transpose(l):
    return [[l[j][i] for j in range(len(l))] for i in range (len(l[0]))]

def tens(n):
    return [[i*10 + k for k in range(10)] for i in range(n)]

def flatten(l):
    return [j for i in l for j in i]

def myqs(l):
    if len(l) <= 1 : return l 
    else:
        return myqs([x for x in l[1:] if x <= l[0]]) + [l[0]] +  myqs([x for x in l if x > l[0]])
    
def without_e(l: list):
    return [i for i in l if 'e' not in i]

def nstutter(s: str):
    liste = s.split(" ")
    temp = " ".join(liste[i] for i in range(1,len(liste)-1) if liste[i-1] != liste[i] and liste[i+1] != liste[i])
    if liste[0] != liste[1]:
        temp = liste[0]+ " " + temp
    if liste[-1] != liste[-2]:
        temp = temp + " " + liste[-1]
    return temp
    

def prefixes(w: str, long_max: int):
    return [w[0:i] for i in range(1, long_max)]

def cube_prefixes(w: str):
    prefixes_list = prefixes(w, len(w))
    return any(3*p in prefixes_list for p in prefixes_list)

def no_cube(w: str):
    for i in range(len(w)):
        prefixes_list = prefixes(w[i:], len(w))
        if any(3*p in prefixes_list for p in prefixes_list):
            return False
    return True


def is_balanced(s: str):
    pile = []
    correspondances = {')':'(', ']':'['}
    for c in s:
        if c in "([": 
            pile.append(c)
        elif c in ")]": 
            if not pile: 
                return False
            if pile[-1] == correspondances[c]:
                pile.pop()
            else:
                return False 
    return not pile

def gen_carres():
    i = 0
    while(True):
        i += 1
        yield i**2


#pas utiliser ca crash le pc
def gen_etoiles_liste():
    return [i*"*" for i in range(10**6)]

def gen_etoile_expr():
    return (i*"*" for i in range(10**6))

def gen_etoiles_yield():
    for i in range(1, 10**6):
        yield i*"*"
