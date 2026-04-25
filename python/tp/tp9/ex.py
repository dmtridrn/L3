#pour MacOs
from pathlib import Path
import shutil

def listfichNomC(p,nom):
    path = Path(p)
    for i in path.rglob(f"{nom}"):
        if i.is_file():
            print(i)

def listfichNomS(p,nom):
    path = Path(p)
    for i in path.rglob("*"):
        if i.is_file() and i.stem == nom:
            print(i)

def listfich(p='.', s=''):
    path = Path(p)
    for i in path.iterdir():
        if i.is_file() and i.name.startswith(s):
            print(i)
    
def listfichr(p='.',s=''):
    path = Path(p)
    for i in path.rglob("*"):
        if i.is_file() and i.name.startswith(s):
            print(i)

def Sauvegarde(L:list):
    p = Path() / "ARCHIVE"
    p.mkdir(exist_ok=True)
    for cpt,s in enumerate(L):
        p1 = p / f"fich_{cpt}.txt"
        p1.write_text(s)
    
def listFichNiv(p, suf):
    path = Path(p)
    fichiers = list(path.glob(f"*.{suf}"))
    fichiers += list(path.glob(f"*/*.{suf}"))
    fichiers += list(path.glob(f"*/*/*.{suf}"))
    for i in fichiers:
        print(i)

def recent_files(p):
    res = []
    path = Path(p)
    for i in path.iterdir():
        if i.is_file():
            res.append((i.stat().st_mtime, i.name))
    res.sort(reverse=True)
    for i in range(min(10,len(res))):
        print(res[i])

def recent_files_rec(p):
    res = []
    path = Path(p)
    for i in path.rglob('*'):
        if i.is_file():
            res.append((i.stat().st_mtime, i.name))
    res.sort(reverse=True)
    for i in range(min(10,len(res))):
        print(res[i])

def ancetreC(p1,p2):
    path1 = Path(p1)
    path2 = set(Path(p2).parents)
    if path1 in path2:
        print(path1)
        return
    for i in path1.parents:
        if i in path2:
            print(i)
            return

def listeGF(p,k):
    val = int(k[:-1])
    match k[-1]:
        case "K":
            mult = 1024
        case "M":
            mult = 1024**2
        case "G":
            mult = 1024**3
    taille = val*mult
    path = Path(p)
    for i in path.rglob("*"):
        if i.is_file():
            if i.stat().st_size > taille:
                print(i)

def rangement(p):
    path = Path(p)
    arch = path.parent / "ARCHIVE"
    arch.mkdir(parents=True, exist_ok=True)
    a = arch / "F1K"
    b = arch / "F1M"
    c = arch / "F100M"
    d = arch / "Fsup"
    for i in [a,b,c,d]:
        i.mkdir(parents=True, exist_ok=True)

    for i in path.rglob("*"):
        if i.is_file():
            match i.stat().st_size:
                case s if s < 1024:
                    shutil.move(i, a)
                case s if 1024 < s < 1024**2:
                    shutil.move(i, b)
                case s if 1024 < s < 100*(1024**2):
                    shutil.move(i, c)
                case _:
                    shutil.move(i, d)