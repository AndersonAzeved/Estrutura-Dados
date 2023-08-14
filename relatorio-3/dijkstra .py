import math

class Pilha: 
    def __init__(self):
        self.pilha = []
        self.vertice = 0
    
    def add_vertice(self, v, i):
        self.pilha.append([v,i])
        self.vertice += 1
        x = self.vertice
        while True:
            if x == 1:
                break
            y = x // 2
            if self.pilha[y-1][0] <= self.pilha[x-1][0]:
                break
            else:
                self.pilha[y-1], self.pilha[x-1] = self.pilha[x-1], self.pilha[y-1]
                x = y
                
    def size(self):
        return self.vertice
    
    def remove_vertice(self):
        z = self.pilha[0]
        self.pilha[0] = self.pilha[self.vertice-1]
        self.pilha.pop()
        self.vertice -= 1
        y = 1
        while True:
            x = 2 * y
            if x > self.vertice:
                break
            if x + 1 <= self.vertice:
                if self.pilha[x][0] < self.pilha[x-1][0]:
                    x += 1
            if self.pilha[y-1][0] <= self.pilha[x-1][0]:
                break
            else:
                self.pilha[y-1], self.pilha[x-1] = self.pilha[x-1], self.pilha[y-1]
                y = x
        return z
    
class Grafo:
    def __init__(self, vertices):
        self.vertices = vertices
        self.grafo = [[0] * self.vertices for i in range(self.vertices)]
    
    def add_aresta(self, x, y, peso):
        self.grafo[x-1][y-1] = peso
    
    def dijkstra(self, start):
        peso_origem = [[-1, 0] for i in range(self.vertices)]
        peso_origem[start-1] = [0, start]
        pilha = Pilha()
        pilha.add_vertice(0, start)
        while pilha.size() > 0:
            distancia, vert = pilha.remove_vertice()
            for i in range(self.vertices):
                if self.grafo[vert-1][i] != 0:
                    if peso_origem[i][0] == -1 or peso_origem[i][0] > distancia + self.grafo[vert-1][i]:
                        peso_origem[i] = [distancia + self.grafo[vert-1][i], vert]
                        pilha.add_vertice(distancia + self.grafo[vert-1][i], i+1)
        return peso_origem
    
    def print_matriz(self):
        print('Matriz adjacências: ')
        for i in range(self.vertices):
            print(self.grafo[i])    
            
    def search(self,dijkstra, start, end, caminho):
        if start == end:
            return caminho
        caminho.append(dijkstra[end])
        Grafo.search(self,dijkstra, start, dijkstra[end][1]-1, caminho) 



##### Main

g = Grafo(25) # Criando grafo com 25 elementos

grafo = [[1, 6, 71], [1, 2, 33], [2, 1, 45], [2, 7, 42], [2, 3, 65], [3, 2, 100], [3, 8, 80], [3, 4, 17], [4, 3, 91], [4, 5, 22], [5, 4, 90], [5, 10, 24], [6, 1, 50], [6, 11, 89], [6, 7, 23], [7, 2, 71], [7, 6, 81], [7, 8, 58], [8, 3, 43], [8, 7, 28], [10, 5, 29], [10, 15, 48], [11, 6, 13], [11, 16, 52], [15, 10, 20], [15, 20, 52], [16, 11, 75], [16, 21, 50], [18, 23, 46], [18, 19, 35], [19, 18, 73], [19, 24, 16], [19, 20, 2], [20, 15, 0], [20, 19, 17], [20, 25, 13], [21, 16, 16], [21, 22, 24], [22, 21, 4], [22, 23, 19], [23, 18, 21], [23, 22, 43], [23, 24, 78], [24, 19, 4], [24, 23, 58], [24, 25, 36], [25, 20, 63], [25, 24, 39]]

for i in range(len(grafo)): # Adicionando o peso as arestas
    g.add_aresta(grafo[i][0],grafo[i][1],grafo[i][2])

start = 1
res = g.dijkstra(start)    
caminho = []
end = 25
g.search(res, start-1, end-1, caminho)
caminho = sorted(caminho)
print("Comprimento do caminho mais curto é %d: " %caminho[len(caminho)-1][0],end="")
for i in range(len(caminho)):
    print(caminho[i][1], end=' -> ')
print(end)