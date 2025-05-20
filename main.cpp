#include <iostream>
#include <list>
#include "Grafo.h"
#include <algorithm>
#include <vector>

using namespace std;

void CoberturaBomberos(Grafo<int> grafo);
void ActualizarAdyacentes(vector<pair<int,int>> &barrios,Grafo<int> grafo,list<int> vertices);
bool OrdenPorSeg(const pair<int,int> &a,const pair<int,int> &b);
void OrdenarDec(vector<pair<int,int>> &lista);

int main()
{
	Grafo<int> grafo;

	for(int i=1;i<13;i++){          //Ejemplo
        	grafo.agregar_vertice(i);
	}

	grafo.agregar_arco(1,2,0);  //Ciudad ejemplo TPE3 A
	grafo.agregar_arco(1,3,0);
	grafo.agregar_arco(1,5,0);
	grafo.agregar_arco(2,5,0);
	grafo.agregar_arco(3,5,0);
	grafo.agregar_arco(3,4,0);
	grafo.agregar_arco(3,6,0);
	grafo.agregar_arco(3,7,0);
	grafo.agregar_arco(3,8,0);
	grafo.agregar_arco(4,5,0);
	grafo.agregar_arco(4,6,0);
	grafo.agregar_arco(4,11,0);
	grafo.agregar_arco(5,11,0);
	grafo.agregar_arco(5,10,0);
	grafo.agregar_arco(6,11,0);
	grafo.agregar_arco(6,8,0);
    	grafo.agregar_arco(7,8,0);
	grafo.agregar_arco(7,12,0);
	grafo.agregar_arco(8,12,0);
	grafo.agregar_arco(8,9,0);
	grafo.agregar_arco(8,11,0);
	grafo.agregar_arco(9,11,0);
	grafo.agregar_arco(9,10,0);
	grafo.agregar_arco(9,12,0);
	grafo.agregar_arco(10,11,0);

    CoberturaBomberos(grafo);
    return 0;
}

bool OrdenPorSeg(const pair<int,int> &a,const pair<int,int> &b){
    return (a.second > b.second);
}

void OrdenarDec(vector<pair<int,int>> &lista){
    sort(lista.begin(), lista.end(), OrdenPorSeg);
}

void ActualizarAdyacentes(vector<pair<int,int>> &barrios,Grafo<int> grafo,list<int> vertices){ //O(v^2)
	for(auto it=vertices.begin();it!=vertices.end();it++){
	        barrios.push_back(make_pair(*it,grafo.cantidad_adyacentes(*it))); //O(v)
	}
        OrdenarDec(barrios);
}


void CoberturaBomberos(Grafo<int> grafo){

    vector<int> solucion;
    list<int> vertices;
    vector<pair<int,int>> barrios;
    grafo.devolver_vertices(vertices);

    ActualizarAdyacentes(barrios,grafo,vertices);

    auto it=barrios.begin();
    while(!barrios.empty()){    //Agrega el vertice con mas cantidad de vecinos sin cubrir a la solución en cada iteracion.

        solucion.push_back(it->first);
        vertices.remove(it->first);
        list<pair<int,int>> adyacentes;
        grafo.devolver_adyacentes(it->first,adyacentes);
        grafo.eliminar_vertice(it->first);
        for(auto itAdy=adyacentes.begin();itAdy!=adyacentes.end();itAdy++){
            vertices.remove(itAdy->first);
            grafo.eliminar_vertice(itAdy->first);
        }
        barrios.clear();
        ActualizarAdyacentes(barrios,grafo,vertices);

    };

    cout<<"Solucion posible: ";
    for(auto it=solucion.begin();it!=solucion.end();it++){
        cout<< *it<<"  ";
    }
}


