#pragma once
#include <iostream>
#include <list>
#include <stack>
using namespace std;

class Graph
{
    int V;	// Количество вершин
    list<int> *adj; //  Указатель на массив, содержащий список смежности
  
    void topologicalSortUtil(int v, bool visited[], stack<int> &Stack);

public:
    Graph(int V);
    void addEdge(int v, int w);
    void topologicalSort();
};
