
//Librerias a Utilizar
#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using std::vector;
using std::cout;
using std::endl;
using std::reverse;


//Prototipos
vector<int> bellmanFord(int numVertices, vector<vector<int>>& aristas, int src );
vector<int> searchBellmanFord(int numVertices, vector<vector<int>>& aristas, int src, int searched);
int main()
{
    cout<<"=====ALGORITMO BELLMAN-FORD=====\n"<<endl;
    //Indicar cuantos vertices hay en el grafo
    int numVertices=5;

    //lista representando las aristas(vertice inicio, vertice destino, peso)
    vector<vector<int>> aristas={
                                   {0,1,2},
                                   {1,2,1},
                                   {2,3,-1},
                                   {3,1,-1},
                                   {3,4,4}

    };

    //establecer el vertice source (inicio)
    int src = 0;

    vector<int> resultados = bellmanFord(numVertices, aristas, src);

    //impresion de resultados
    cout<<"--Distancia minima entre de todos los vertices--"<<endl;
    for(int distancia : resultados){
        cout<<"["<<distancia<<"] ";
    }
    cout<<"\n\n"<<endl;

    //busqueda del camino de un vertice en especifico
    cout<<"\n---Busqueda de Vertice Especifico---"<<endl;
    int toSearch= 3;
    vector<int> caminoMasCorto = searchBellmanFord(numVertices, aristas, src, toSearch);
    if(!caminoMasCorto.empty() && caminoMasCorto[0]==-100){
        cout<<">>[ERROR]: El nodo buscado se encuentra dentro de un CICLO NEGATIVO INFINITO"<<endl;
    }else if(caminoMasCorto.empty()){
        cout<<">>[AVISO]: El vertice buscado no es alcanzable desde la raiz"<<endl;
    }else{
        for(int vertice: caminoMasCorto){
            if(vertice!=toSearch){
                cout<<"["<<vertice<<"]->";
            }else{
                cout<<"["<<vertice<<"] ";
            }
        }
        cout<<"\nDistancia: "<<resultados[toSearch];
    }

    cout<<"\n================================"<<endl;
    return 0;
}


vector<int> bellmanFord(int numVertices, vector<vector<int> > &aristas, int src){
    //inicializamos todas las distancias entre los vertices existentes
    vector<int> dist(numVertices, INT_MAX);
    dist[src] =0;

    //bandera que detectamos ciclo
    bool cicloDetectado= false;

    //propagacion gradual
    for(int i=0; i< numVertices; i++){

        //analisis de distancia entre vertices por medio de analisis de aristas
        for(vector<int> edge: aristas){
            int inicio = edge[0];
            int fin= edge[1];
            int peso= edge[2];


            //comparacion de distancia
            if(dist[inicio] !=INT_MAX && dist[inicio]+peso < dist[fin]){

                //verificacion que ocurra un ciclo infinito negativo
                if(i == numVertices-1){
                    dist[fin] = -100;
                    cicloDetectado=true;
                }else{
                    //actualizamos el valor de la distancia
                    dist[fin]= dist[inicio]+peso;
                }
            }
        }

        if(cicloDetectado){
            return dist;
        }
    }

    //retornamos valores de distancias
    return dist;
}

//*
vector<int> searchBellmanFord(int numVertices, vector<vector<int> > &aristas, int src, int searched){
    vector<int> dist(numVertices, INT_MAX);
    vector<int> predecesores(numVertices, -1);
    dist[src] =0;

    //bandera que detectamos ciclo
    bool cicloDetectado= false;

    for(int i=0; i<numVertices; i++){

        for(vector<int> edge: aristas){
            int inicio = edge[0];
            int fin = edge[1];
            int peso= edge[2];

            if(dist[inicio] !=INT_MAX && dist[inicio]+peso<dist[fin]){

                //verificacion que ocurra un ciclo infinito negativo
                if(i == numVertices-1){
                    dist[fin] = -100;
                    cicloDetectado=true;
                }else{
                    //actualizamos el valor de la distancia
                    dist[fin]= dist[inicio]+peso;
                    //guardamos el predecesor del vertice al que nos movemos
                    predecesores[fin]= inicio;
                }
            }
        }
    }


    //--Proceso para devolver el trayecto hacia el vertice buscado--

    vector<int> camino;

    //revisamos que el haya verdaderamente una conexion hacia el nodo buscado
    if(dist[searched] == INT_MAX){
        //camino vacio
        return {};
    }

    if(cicloDetectado){
        //revisamos que el vertice buscado no este atrapado en un ciclo infinito
        if(dist[searched]==-100){
            return {-100};
        }
    }

    int actual = searched;
    while(actual !=-1){
        //guardamos la ubicacion
        camino.push_back(actual);
        //nos movemos hacia el predecesor de la ubicacion actual
        actual = predecesores[actual];
    }

    //reordenamos el orden del camino, ya que se habia guardado al reves
    reverse(camino.begin(), camino.end());

    return camino;
}
