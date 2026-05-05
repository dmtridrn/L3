import re
from pathlib import Path
import shutil

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
print(f"{jour}, {zon}")

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
        res.append(i)
    return sorted(res, key=lambda x: x.stat().st_mtime, reverse=True)[:n]

print(recent_txt(".", 10))