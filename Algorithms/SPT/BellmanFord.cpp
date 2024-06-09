#include "BellmanFord.h"
int BellmanFord::totalCost = 0;
BellmanFord::SPTVertex* BellmanFord::vertex = nullptr;

EdgeList BellmanFord::getSPT(IncidenceMatrix *matrix, int start) {
    int vertNum = (int)matrix->getNumVertices();
    int edgeNum = (int)matrix->getNumEdges();
    vertex = new SPTVertex[vertNum];
    vertex[start].parent = start;
    vertex[start].minWeight = 0;

    for(int k = 0; k < vertNum - 1; k++){
        for(int i = 0; i < edgeNum; i++){
            int tempStart = -1;
            int tempEnd = -1;
            int tempWeight = -1;
            for(int j = 0; j < vertNum; j++){
                if(matrix->getMatrix()[j][i] > 0) {
                    tempWeight = matrix->getMatrix()[j][i];
                    tempStart = j;
                }
                else if(matrix->getMatrix()[j][i] == -1) tempEnd = j;
                if(tempStart != -1 && tempEnd != -1) break;
            }
            if(vertex[tempStart].minWeight != -1){
                if(vertex[tempEnd].minWeight > tempWeight + vertex[tempStart].minWeight  || vertex[tempEnd].minWeight == -1){
                    vertex[tempEnd].minWeight = tempWeight + vertex[tempStart].minWeight;
                    vertex[tempEnd].parent = tempStart;
                }
            }
        }
    }

    auto* edges = new EdgeList::Edge[vertNum];
    int j = 0;
    for (int i = 0; i < vertNum; i++) {
        edges[j].start = vertex[i].parent;
        edges[j].end = i;
        edges[j].weight = vertex[i].minWeight;
        j++;
    }

    return {(unsigned  int)vertNum, (unsigned  int)vertNum, edges};
}

EdgeList BellmanFord::getSPT(AdjacencyList *list, int start) {
    int vertNum = (int)list->getVertices();
    vertex = new SPTVertex[vertNum];
    vertex[start].parent = start;
    vertex[start].minWeight = 0;

    for(int k = 0; k < vertNum - 1; k++){

        for(int i = 0; i < vertNum; i++){
            for(int j = 0; j < list->getAdjList()[i].size; j++){
                int tempStart = i;
                int tempEnd = (int)list->getAdjList()[i].list[j].dest;
                int tempWeight = list->getAdjList()[i].list[j].weight;
                if(tempWeight == -1) continue;
                if(vertex[tempStart].minWeight != -1){
                    if(vertex[tempEnd].minWeight > tempWeight + vertex[tempStart].minWeight  || vertex[tempEnd].minWeight == -1){
                        vertex[tempEnd].minWeight = tempWeight + vertex[tempStart].minWeight;
                        vertex[tempEnd].parent = tempStart;
                    }
                }
            }
        }
    }

    auto* edges = new EdgeList::Edge[vertNum];
    int j = 0;
    for (int i = 0; i < vertNum; i++) {
        edges[j].start = vertex[i].parent;
        edges[j].end = i;
        edges[j].weight = vertex[i].minWeight;
        j++;
    }

    return {(unsigned  int)vertNum, (unsigned  int)vertNum, edges};
}

int* BellmanFord::getPath(int start, int end) {
    // Sprawdzenie, czy istnieje ścieżka
    if (vertex[end].minWeight == -1) {
        return nullptr;
    }

    // Liczenie długości ścieżki
    int length = 0;
    totalCost = 0;  // Resetowanie totalCost przed rozpoczęciem obliczeń
    for (int v = end; v != start; v = vertex[v].parent) {
        totalCost += vertex[v].minWeight - vertex[vertex[v].parent].minWeight;  // Dodanie wagi aktualnej krawędzi do totalCost
        length++;
    }
    length++; // Dodanie wierzchołka startowego

    // Tworzenie tablicy wynikowej
    int* path = new int[length];
    int index = length - 1;

    // Wypełnianie tablicy ścieżki
    for (int v = end; v != start; v = vertex[v].parent) {
        path[index--] = v;
    }
    path[index] = start;

    return path;
}

void BellmanFord::printPath( const EdgeList& edgesWrap, int start, int end) {
    if (edgesWrap.edges[end].weight == -1) {
        std::cout << "Nie ma dostępnej sciezki z " << edgesWrap.edges[0].start << " do " << end << std::endl;
        return;
    }
    int* path = getPath(start, end);

    std::cout << "Najkrotsza sciezka z " << start << " do " << end << ": ";
    int j = 0;
    while(path[j] != end){
        std::cout << path[j] << " -- > ";
        j++;
    }
    std::cout << end << std::endl;
    std::cout << "\nDlugosc sciezki: " << totalCost << std::endl;
}