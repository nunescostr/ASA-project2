#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
#include <chrono>

using namespace std;
using namespace std::chrono;


class Aresta
{
private:
    int _v1, _v2, _p;

public:
    Aresta(int v1, int v2, int p){
        _v1 = v1;
        _v2 = v2;
        _p = p;
    };

    int get_v1(){
        return _v1;
    }

    int get_v2(){
        return _v2;
    }

    int get_peso(){
        return _p;
    }

    bool operator < (const Aresta& aresta2) const
	{
		return (_p < aresta2._p);
	}
};

vector<Aresta> arestas;

void get_vertices(){
    int arcos;
    scanf("%d\n", &arcos);

    int v1,v2,p;

    for (int i = 0; i < arcos; i++){
        scanf("%d %d %d",&v1,&v2,&p);
        v1--;v2--;
        arestas.push_back(Aresta(v1,v2,p));
    }
}


class Grafo{

public: 
    Grafo()
	{}

    int find(int conjunto[], int a){
        if (conjunto[a] == -1){
            return a;
        }
        return find(conjunto,conjunto[a]);
    }

    void union_xy(int conjunto[], int v1, int v2){
        int v1_set = find(conjunto, v1);
        int v2_set = find(conjunto, v2);
        conjunto[v1_set] = v2_set;
    }

    long kruskal_algorithm(int v){
        vector<Aresta> arvore;
        long cost, minCost = 0;
        long size = arestas.size();

        sort(arestas.rbegin(), arestas.rend());
        

        int *conjunto = new int[v];


        memset(conjunto, -1, sizeof(int) * v);
    

        for(int i = 0; i < size; i++){
            int v1 = find(conjunto, arestas[i].get_v1());
			int v2 = find(conjunto, arestas[i].get_v2());
            cost = arestas[i].get_peso();

			if(v1 != v2)
			{   
                minCost += cost;
				arvore.push_back(arestas[i]);
				union_xy(conjunto, v1, v2);
			}
        }

        return minCost;

    }
};

int main(){
    auto start = high_resolution_clock::now();
    Grafo g;
    int ver_num;
    scanf("%d\n", &ver_num);
    get_vertices();
    cout<<g.kruskal_algorithm(ver_num)<<endl;
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: "<< duration.count() << " microseconds" << endl;
    return 0;
}
