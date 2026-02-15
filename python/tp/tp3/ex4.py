import random
import time

def init_table(n):
    return [None for i in range(n)]

def add_elt(x,n,t):
    idx = x%n
    for _ in range(n):
        if t[idx] == None or t[idx] == x:
            t[idx] = x
            return True
        else: 
            idx = (idx+1)%n
    return False

def in_table(x,n,t):
    idx = x%n
    for i in range(n):
        if t[idx] == x:
           return True
        else: 
            idx = (idx+1)%n
    return False

def test_hash(n,l):
    t = init_table(n)
    for elt in l:
        add_elt(elt, n, t)
    for elt in l:
        if not in_table(elt, n, t):
            return False
    return True

def test_set(l):
    t = set()
    for elt in l:
        t.add(elt)
    for elt in l:
        if not elt in t:
            return False
    return True

def hash_benchmark(k, m, n):
    # 1. Création de la liste de k entiers entre 0 et m [cite: 207, 210]
    l = [random.randint(0, m) for _ in range(k)]
    
    # 2. Chronométrage de test_hash [cite: 195, 207]
    t1_hash = time.process_time()
    test_hash(n, l)
    t2_hash = time.process_time()
    duree_hash = t2_hash - t1_hash
    
    # 3. Chronométrage de test_set [cite: 200, 207]
    t1_set = time.process_time()
    test_set(l)
    t2_set = time.process_time()
    duree_set = t2_set - t1_set
    
    # 4. Affichage des résultats 
    print(f"Résultats pour k={k}, m={m}, n={n}:")
    print(f"Temps Table de hachage 'maison' : {duree_hash:.6f} secondes")
    print(f"Temps Ensemble Python (set)     : {duree_set:.6f} secondes")


hash_benchmark(90000, 100000, 100000)


