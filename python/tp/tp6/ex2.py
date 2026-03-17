import re

def filtre1(nomfic):
    m = r"\w{8,12}\b"
    motif = re.compile(m)
    with open(nomfic, 'r') as f:
        for ligne in f:
            if motif.match(ligne):
                print(ligne.strip())

def filtre2(nomfic):
    m = r"\btoto\b"
    motif = re.compile(m)
    with open(nomfic, 'r') as f:
        for ligne in f:
            if motif.search(ligne):
                print(ligne.strip())

def filtre3(nomfic):
    m = r"(.*\btoto\b.*){3,}"
    motif = re.compile(m)
    with open(nomfic, 'r') as f:
        for ligne in f:
            if motif.search(ligne):
                print(ligne.strip())

def filtre4(nomfic):
    m = r"\b[a-z]+\b "
    motif = re.compile(m)
    with open(nomfic, 'r') as f:
        for ligne in f:
            if motif.search(ligne):
                print(ligne.strip())

if __name__ == "__main__":
    filtre3("test.txt")
    