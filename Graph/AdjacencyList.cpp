#include "AdjacencyList.h"
#include <cstdlib>
#include <iostream>
#include <iomanip>

AdjacencyList::AdjacencyList(int vertices): vertices(vertices) {
    adjList = new EdgeList[vertices];
}

AdjacencyList::~AdjacencyList() {
    for (int i = 0; i < vertices; ++i) {
        delete[] adjList[i].list;
    }
    delete[] adjList;
}

void AdjacencyList::addEdge(unsigned int startVertex, unsigned int endVertex, int weight) {
    if(adjList[startVertex].list == nullptr){
        adjList[startVertex].list = new Edge[1]{Edge{endVertex, weight}};
        adjList[startVertex].size += 1;
    } else {
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


