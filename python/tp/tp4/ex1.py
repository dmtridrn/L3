import random as r
import string
def deviner(k):
    nombre = r.randint(0,k)
    while(True):
        try:
            tentative = int(input(f"entre un nombre entre 0 et {k}:  "))
            if tentative < nombre:
                print("PLUS")
            elif tentative > nombre:
                print("MOINS")
            else:
                print("YES")
                break
        except (EOFError, KeyboardInterrupt):
            print(nombre)
            break
        except ValueError:
            print("Que des ints svp")
    print("BYE BYE")

def frequence(nomfich: str, maxlen=5):
    d = dict()
    with open(nomfich, 'r') as f:
        for l in f:
            l.lower().strip(string.punctuation)
            m = l.split()
            for mot in m:
                if len(mot) > maxlen:
                    d[mot] = d.get(mot, 0) + 1
    p = sorted(d.items(), key=lambda x:x[1], reverse=True)
    for i in range(5):
        print(p[i])


def corrige(nomdico: str, nomfich: str):
    f1 = open(nomfich, 'r')
    f2 = open(nomdico, 'r')
    nfich = nomfich.split(".")
    f3 = open(nfich[0] + "_corrige." + nfich[1], 'w')
    
    langue = f2.read()
    f2.close()
    for l in f1:
        m = l.split()
        for w in m:
            w2 = w.lower().strip(string.punctuation)
            if w2 not in langue:
                w = "**"+w+"**"
            f3.write(w + "\n")
    f1.close()
    f3.close()

corrige("dico_light.txt", "proust2.txt")