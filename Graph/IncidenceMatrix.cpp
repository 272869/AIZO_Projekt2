#include <iostream>
#include <iomanip>
#include "IncidenceMatrix.h"

IncidenceMatrix::IncidenceMatrix(unsigned int vertices, unsigned int edges) {
    IncidenceMatrix::numVertices = vertices;
    IncidenceMatrix::numEdges = edges;

    matrix = new int *[vertices];
    //Tworzy dynamiczną tablicę wskaźników matrix, gdzie każdy wskaźnik wskazuje na tablicę o długości edges.
    for (int i = 0; i < vertices; ++i) {
        matrix[i] = new int[edges];
        for(int j = 0; j < edges; j++){
            matrix[i][j] = 0; // inicjalizuje wszystkie elementy macierzy wartościami 0.
        }
    }
}

IncidenceMatrix::~IncidenceMatrix() {
    for (int i = 0; i < numVertices; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void IncidenceMatrix::addEdge(unsigned int startVertex, unsigned int endVertex, unsigned short weight, unsigned int edge) {
    //Upewnia się, że startVertex i endVertex są mniejsze niż liczba wierzchołków, a edge jest mniejszy niż liczba krawędzi.
    if(startVertex < numVertices && endVertex < numVertices && edge < numEdges){
        matrix[startVertex][edge] = weight; //Ustawia wage krawędzi dla wierzchołka początkowego.
        matrix[endVertex][edge] = -1;
    }
}


void IncidenceMatrix::print(){
    std::cout << "    ";
    for (int i = 0; i < numEdges; i++){
        std::cout << std::setw(2) << i << "   ";
    }
    std::cout << std::endl;
    for (int i = 0; i < numVertices; i++){
        std::cout << std::setw(3) << i << "  ";
        for (int j = 0; j < numEdges; j++){
            std::cout << std::setw(2) << matrix[i][j] << " | ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int **IncidenceMatrix::getMatrix() const {
    return matrix;
}

unsigned int IncidenceMatrix::getNumVertices() const {
    return numVertices;
}

unsigned int IncidenceMatrix::getNumEdges() const {
    return numEdges;
}
