import re
from pathlib import Path
import shutil
import random

def prefixes(x):
    return [x[:i] for i in range(len(x)+1)]

def plpc(x:str,y:str):
    res = ""
    for i in range(min(len(x), len(y))):
        if x[i] == y[i]:
            res += x[i]
        else:
            break
    return res

def diags(m):
    return [m[i][i] for i in range(len(m))], [m[i][len(m)-i-1] for i in range(len(m))]

IP_format = r"(\d{1,3}\.){3}\d{1,3}"
motif = re.compile(IP_format)

def ip(ligne):
    res = motif.match(ligne)
    if res:
        return res.group(0)

date_format = r"\[(\d{2})/([a-zA-Z]{3})/(\d{4}):(\d{2}):(\d{2}):(\d{2}) ([+-]\d{4})]"
date_str = '[10/Oct/2000:13:55:36 -0700]'
date_regex = re.compile(date_format)
mobj = date_regex.fullmatch(date_str)
jour = mobj.group(1)
zon = mobj.group(7)
#print(f"{jour}, {zon}")


def top10(nomf):
    d = dict()
    with open(nomf) as f:
        for l in f:
            ipadr = ip(l)
            d[ipadr] = d.get(ipadr, 0) + 1
    iptrie = sorted([(i,a) for (a,i) in d.items()], reverse=True)
    return iptrie[:10]


def Lfich_txt():
    path = Path(".")
    for i in path.rglob("*.txt"):
        print(i)

def recent_txt(nomdir, n):
    path = Path(nomdir)
    res = []
    for i in path.rglob("*.txt"):
        if(i.is_file()):
            res.append(i)
    return sorted(res, key=lambda x: x.stat().st_mtime, reverse=True)[:n]

class tournoi:
    
    def __init__(self, L):
        self.statut = dict()
        for i in L:
            self.statut[i] = self.statut.get(i,'D')
        self.res = dict()
        self.encours = []

    def nouv_match(self):
        dispo = set()
        #on get toutes les équipes dispo
        for i,j in self.statut.items():
            if j == 'D' and len(self.res[e1]) < len(self.statut)-1: #on ajoute que s'ils ont pas fait tous leurs match
                dispo.add(i)
        #on en récup 2
        e1 = random.choice(dispo)
        dispo.pop(e1)
        for i,j in self.res[e1]:
            dispo.pop(i) #on vire ceux que e1 a déjà joué
        e2 = random.choice(dispo)
        #ils jouent
        self.statut[e1] = 'J'
        self.statut[e2] = 'J'
        self.encours.append(e1,e2)
        print(f"Nouveau match: {e1} - {e2}")

    def resultat(self, e1, e2):
        for i in range(len(self.encours)):
            if self.encours[i] == (e1,e2) or self.encours[i] == (e2,e1):
                self.encours.pop(i)
                self.statut[e1] = 'D' #le gagnant est dispo
                self.res[e1].append((e2, True))
                self.res[e2].append((e1, False))
                derniers_match = list(self.res[e2])[-3:]
                for j,k in derniers_match:
                    if k == True:
                        self.statut[e2] = 'D' #il a win un match sur ses trois derniers
                        return
                self.statut[e2] = 'E'
                return
        print("Veuillez rentrer un match valide")
    
    