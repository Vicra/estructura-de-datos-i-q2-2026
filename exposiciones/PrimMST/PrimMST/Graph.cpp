#include "Graph.h"
#include <iostream>
#include <climits>

using std::cout;
using std::endl;

Graph::Graph(int vertices) {
    this->vertices = vertices;

    matriz = new int*[vertices];
    for (int i = 0; i < vertices; i++) {
        matriz[i] = new int[vertices];
        for(int j = 0; j < vertices; j++) {
            matriz[i][j] = 0;
        }
    }
}

Graph::~Graph() {
    for (int i = 0; i < vertices; i++) {
        delete[] matriz[i];
    }
    delete[] matriz;
}

void Graph::agregarArista(int u, int v, int peso) {
    matriz[u][v] = peso;
    matriz[v][u] = peso;
}

int Graph::indiceMenor(int clave[], bool enMST[]) {
    int min = INT_MAX;
    int indice = -1;

    for (int v = 0; v < vertices; v++) {
        if (enMST[v] == false && clave[v] < min) {
            min = clave[v];
            indice = v;
        }
    }
    return indice;
}

void Graph::imprimirMST(int padre[]) {
    int total = 0;
    cout << "Arista \t Peso" << endl;
    for (int i = 1; i < vertices; i++) {
        cout << padre[i] << " - " << i << " \t " << matriz[padre[i]][i] << endl;
        total += matriz[padre[i]][i];
    }
    cout << "Peso total del MST: " << total << endl;
}

void Graph::prim() {
    int* clave = new int[vertices];
    int* padre = new int[vertices];
    bool* enMST = new bool[vertices];

    for (int i = 0; i < vertices; i++) {
        clave[i] = INT_MAX;
        enMST[i] = false;
        padre[i] = -1;
    }

    clave[0] = 0;

    for (int count = 0; count < vertices - 1; count++) {
        int u = indiceMenor(clave, enMST);
        enMST[u] = true;

        for (int v = 0; v < vertices; v++) {
            if (matriz[u][v] != 0 && enMST[v] == false && matriz[u][v] < clave[v]) {
                padre[v] = u;
                clave[v] = matriz[u][v];
            }
        }
    }

    imprimirMST(padre);

    delete[] clave;
    delete[] padre;
    delete[] enMST;
}
