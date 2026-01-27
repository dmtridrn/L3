from time import process_time

def count_blanks(s):
    cpt = 0
    for c in s:
        if c == ' ':
            cpt+=1
    return cpt

def is_palindrome(s):
    return s == s[::-1]

def count(s, o):
    if not o:
        return 0
    cpt = 0
    i = 0
    while i < len(s):
        pos = s.find(o, i)
        if pos == -1:
            break
        cpt += 1
        i = pos + len(o)
    return cpt

debut = process_time()

count(1000000*"aaaaajjajjaaajjjjjj", "jj")


fin = process_time()

temps = fin - debut

print(f"Temps CPU utilisé pour la mienne: {temps:.4f} secondes")

debut = process_time()

str.count(100000*"aaaaajjajjaaajjjjjj", "jj")


fin = process_time()

temps = fin - debut

print(f"Temps CPU utilisé pour str: {temps:.4f} secondes")
