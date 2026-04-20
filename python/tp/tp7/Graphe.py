import re
import heapq
import math

class Graphe:

    def __init__(self, fic:str):
        self._S = []
        self._A = {}
        self.construireG(fic)
    
    def ajouter(self, x, y, d):
        if x not in self._S:
            self._S.append(x)
        if x not in self._A:
            self._A[x] = []
        if y not in self._S:
            self._S.append(y)
        self._A[x].append((y,d))

    def __str__(self):
        res = ""
        for i in self._S:
            if i in self._A:
                for succ,poids in self._A[i]:
                    res += f"{i} --{poids}--> {succ}\n"
            else:
                res += f"{i}\n"
        return res
    
    def __len__(self):
        return len(self._S)
    
    def poids(self, x, y):
        if x not in self._A:
            return None
        for dest,poi in self._A[x]:
            if dest == y:
                return poi
        return None
    
    def succ(self,x):
        res = []
        if x not in self._A:
            return None
        for dest,poi in self._A[x]:
            res.append(dest)
        return res
    
    def __iter__(self):
        for i in self._S:
            yield i
    
    
    def construireG(self, fic:str):
        m = r"(\S+) - (-?\d+(?:\.\d+)?) -> (\S+)"
        motif = re.compile(m)
        with open(fic, 'r') as f:
            flag = False
            for l in f:
                if l.strip() == "Transitions":
                    flag = True
                    continue
                if not flag:
                    continue
                res = motif.match(l)
                if res:
                    self.ajouter(res.group(1), res.group(3), float(res.group(2)))

##########  TP8  #########

    def Dijkstra(self, source):
        dist = {}
        pred = {}
        track = set()
        for sommet in self._S:
            dist[sommet] = math.inf
            pred[sommet] = None
        dist[source] = 0
        file = [(dist[u], u) for u in self._S]
        heapq.heapify(file)
        while file:
            (d,u) = heapq.heappop(file)
            if (u not in self._A) or (u in track):
                continue
            track.add(u)
            for v,poids in self._A[u]:
                if dist[v] > dist[u] + poids:
                    dist[v] = dist[u] + poids
                    heapq.heappush(file, (dist[v],v))
                    pred[v] = u
        return dist, pred

    def Bellman(self, source):
        dist = {}
        pred = {}
        for sommet in self._S:
            dist[sommet] = math.inf
            pred[sommet] = None
        dist[source] = 0
        arcs = [(u, v, p) for u in self._A for v, p in self._A[u]]
        for k in range(1, len(self._S)):
            for u,v,poids in arcs:
                if dist[v] > dist[u] + poids:
                    dist[v] = dist[u] + poids
                    pred[v] = u
        for u,v,poids in arcs:
            if dist[v] > dist[u] + poids:
                return None,None
        return dist, pred


g = Graphe("tp7/g3.txt")
print(g)
print(g.Bellman("q0"))