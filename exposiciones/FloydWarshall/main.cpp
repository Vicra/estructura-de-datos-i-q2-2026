#include <iostream>
#include <vector>
using std::vector;
using std::cout;
using std::cin;
using std::endl;

const int INF = 1e9;

void imprimirMatriz(const vector<vector<int>>& matriz)
{
    int N = matriz.size();
    cout << endl;
    for(int i = 0; i < N; ++i)
    {
        for(int j = 0; j < N; ++j)
        {
            if(matriz[i][j] == INF)
                cout << "| INF ";
            else
                cout << "|  " << matriz[i][j] << "  ";
        }
        cout << "|\n";
    }
    cout << "\n";
    cout << endl;
}

void floydWarshall(vector<vector<int>>& dist)
{
    int N = dist.size();
    for(int k = 0; k < N; ++k)
    {
        for(int i = 0; i < N; ++i)
        {
            for(int j = 0; j < N; ++j)
            {
                bool cond1 = (dist[i][k] != INF);
                bool cond2 = (dist[k][j] != INF);

                if(cond1 && cond2)
                {
                    int viejo = dist[i][j];
                    int nuevo = dist[i][k] + dist[k][j];

                    cout << "Evaluando dist[" << i << "][" << j << "] usando k = " << k << "\n";
                    cout << "    Condiciones: "
                         << dist[i][k] << " < " << INF << (cond1 ? " ✓ " : " X ")
                         << "  |  "
                         << dist[k][j] << " < " << INF << (cond2 ? " ✓ " : " X ") << endl;
                    cout << "   Comparando: min(" << viejo << ", " << dist[i][k] << " + " << dist[k][j]
                         << ") = min(" << viejo << ", " << nuevo << ")\n";
                    if(nuevo < viejo)
                    {
                        dist[i][j] = nuevo;
                        imprimirMatriz(dist);
                    }
                    else
                    {
                        cout << "   No se actualiza: " << viejo << " ≤ " << nuevo << "\n";
                    }
                }
                else
                {
                    cout << "NO HUBO cambio en dist[" << i << "][" << j << "] " << endl;
                    cout << "    Condiciones: "
                         << dist[i][k] << " < " << INF << (cond1 ? " ✓ " : " X ")
                         << "  |  "
                         << dist[k][j] << " < " << INF << (cond2 ? " ✓ " : " X ") << endl;
                }
                cout << "-------------------------\n";
            }
        }
    }

    for (int i = 0; i < N; ++i)
    {
        if(dist[i][i] < 0)
        {
            cout << "Existe un ciclo negativo en el nodo " << i << "!\n";
            return;
        }
    }
    cout << "No se detectaron ciclos negativos.\n";
}

int main()
{
    int N = 4;
    vector<vector<int>> dist =
    {
        //1   2    3     4
        {0,   3, INF,   7}, //1
        {8,   0,   2, INF}, //2
        {5, INF,   0,   1}, //3
        {2, INF, INF,   0}  //4
    };

    cout << "Matriz inicial:\n";
    imprimirMatriz(dist);

    floydWarshall(dist);

    cout << "Matriz de distancias mas cortas:\n";
    imprimirMatriz(dist);

    return 0;
}
