def count_blanks(s):
    cpt = 0
    for c in s:
        if c == ' ':
            cpt+=1
    return cpt

def is_palindrome(s):
    return s == s[::-1]

def count(s,o):
    lon = len(o)
    i = 0
    cpt = 0
    while i < len(s)-len(o)+1:
        if s[i:i+lon] == o:
            cpt+=1
            i+=lon
        else:
            i+=1
    return cpt

