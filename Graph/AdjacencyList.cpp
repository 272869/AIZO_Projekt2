#include "AdjacencyList.h"
#include <cstdlib>
#include <iostream>
#include <iomanip>

AdjacencyList::AdjacencyList(int vertices): vertices(vertices) {
    adjList = new EdgeList[vertices]; //lista sasiedztwa dla kazdego wierzcholka
}

AdjacencyList::~AdjacencyList() {
    for (int i = 0; i < vertices; ++i) {
        delete[] adjList[i].list;
    }
    delete[] adjList;
}

void AdjacencyList::addEdge(unsigned int startVertex, unsigned int endVertex, int weight) {
    if(adjList[startVertex].list == nullptr){
        adjList[startVertex].list = new Edge[1]{Edge{endVertex, weight}}; //Jeśli lista sąsiedztwa dla danego wierzchołka jest pusta, alokuje pamięć na nową krawędź.
        adjList[startVertex].size += 1;
    } else { //W przeciwnym razie, realokuje pamięć dla nowej krawędzi i przepisuje istniejące krawędzie.
        size_t newSize = sizeof(Edge) * (adjList[startVertex].size + 1);
        Edge* temp = static_cast<Edge*>(std::realloc(adjList[startVertex].list, newSize));

        if (temp == nullptr) {
            std::cerr << "Failed to reallocate memory for adjacency list." << std::endl;
            return;
        }

        adjList[startVertex].list = temp;
        adjList[startVertex].list[adjList[startVertex].size++] = Edge(endVertex, weight);
    }
    if(weight > -1) addEdge(endVertex, startVertex, -1);
    //tutaj dodajemy krawędź odwrotną przydatną w grafie nieskierowanym
    // jesli np. od 0 do 4 jest krawędz z waga 5 to od 4 do 0 jest tworzona krawedz z -1, aby bylo wiadomo ze taka istnieje
    //ale w grafie skierowanym nie jest ona brana po uwagę
}


void AdjacencyList::print(){
    for (size_t i = 0; i < vertices; i++){
        std::cout << std::setw(2) << i << " --> ";
        for (int j = 0; j < adjList[i].size; j++) {
            std::cout << std::setw(2) << adjList[i].list[j].dest << '[' << std::setw(2) << adjList[i].list[j].weight << "] | ";
        }
        std::cout << std::endl;
    }
}

int AdjacencyList::getVertices() const {
    return vertices;
}

AdjacencyList::EdgeList *AdjacencyList::getAdjList() const {
    return adjList;
}


