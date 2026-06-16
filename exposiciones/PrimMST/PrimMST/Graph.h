#ifndef GRAPH_H
#define GRAPH_H

class Graph {
private:
    int vertices;
    int** matriz;

    int indiceMenor(int clave[], bool enMST[]);
    void imprimirMST(int padre[]);

public:
    Graph(int vertices);
    ~Graph();

    void agregarArista(int u, int v, int peso);
    void prim();
};

#endif // GRAPH_H
