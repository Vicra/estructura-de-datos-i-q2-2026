#include <iostream>
#include "Graph.h"
#include "windows.h"

using std::cout;
using std::endl;

int main() {

    SetConsoleOutputCP(65001);

    Graph g(5);

    g.agregarArista(0, 1, 2);
    g.agregarArista(0, 3, 6);
    g.agregarArista(1, 2, 3);
    g.agregarArista(1, 3, 8);
    g.agregarArista(1, 4, 5);
    g.agregarArista(2, 4, 7);
    g.agregarArista(3, 4, 9);

    cout << "=== Árbol de Expansión Mínima (PRIM) ===" << endl;
    g.prim();

    return 0;
}
