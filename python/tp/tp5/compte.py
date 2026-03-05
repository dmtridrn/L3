import random as r

def configinit(n,k,v):
    liste = [r.randint(1,k-1) for i in range(n)]
    goal = r.randint(1,v)
    return liste, goal
