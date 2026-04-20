class File:
    def __init__(self):
        self.Tin = []
        self.Tout = []

    def enfiler(self, elt):
        self.Tin.append(elt)
    
    def defiler(self):
        if not self.Tout:
            while self.Tin:
                self.Tout.append(self.Tin.pop())
        if not self.Tout:
            return None
        return self.Tout.pop()

    def __iter__(self):
        for i in range(len(self.Tout)-1, -1, -1):
            yield self.Tout[i]
        for i in self.Tin:
            yield i
    
    