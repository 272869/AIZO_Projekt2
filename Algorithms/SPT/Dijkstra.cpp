#include "Dijkstra.h"

int Dijkstra::totalCost = 0;
Dijkstra::SPTVertex* Dijkstra::vertex = nullptr;

int* Dijkstra::getPath(int start, int end) {
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


EdgeList Dijkstra::getSPT(IncidenceMatrix *matrix, int start) {
    int vertNum = (int)matrix->getNumVertices();
    vertex = new SPTVertex[vertNum];
    vertex[start].parent = start;
    vertex[start].minWeight = 0;


    for(int k = 0; k < vertNum - 1; k++) {
        int minParentWeight = -1;
        int minParent = -1;
        for (int i = 0; i < vertNum; i++) {
            if (!vertex[i].visited && vertex[i].minWeight > -1
                && (vertex[i].minWeight < minParentWeight || minParentWeight == -1)) {
                minParentWeight = vertex[i].minWeight;
                minParent = i;
            }
        }
        if(minParent == -1) break;

        for (int i = 0; i < matrix->getNumEdges(); i++) {
            int tempParWeight = matrix->getMatrix()[minParent][i];
            if (tempParWeight > 0) {
                for (int j = 0; j < vertNum; j++) {
                    if (minParent == j) continue;
                    int tempChildWeight = matrix->getMatrix()[j][i];
                    if (tempChildWeight != 0) {
                        if (!vertex[j].visited && (vertex[j].minWeight > tempParWeight + vertex[minParent].minWeight  || vertex[j].minWeight == -1)) {
                            vertex[j].minWeight = tempParWeight + vertex[minParent].minWeight;
                            vertex[j].parent = minParent;
                        }
                    }
                }
            }
        }
        vertex[minParent].visited = true;
    }
    auto* edges = new EdgeList::Edge[vertNum];
    int j = 0;
    for (int i = 0; i < vertNum; i++) {
         // Pomijamy wierzchołek startowy
            edges[j].start = vertex[i].parent;
            edges[j].end = i;
            edges[j].weight = vertex[i].minWeight;
            j++;

    }

    return {(unsigned  int)vertNum, (unsigned  int)vertNum, edges};
}

EdgeList Dijkstra::getSPT(AdjacencyList *list, int start) {
    int vertNum = (int)list->getVertices();
    vertex = new SPTVertex[vertNum];
    vertex[start].parent = start;
    vertex[start].minWeight = 0;

    for(int k = 0; k < vertNum - 1; k++) {
        int minParentWeight = -1;
        int minParent = -1;
        for (int i = 0; i < vertNum; i++) {
            if (!vertex[i].visited && vertex[i].minWeight > -1
                && (vertex[i].minWeight < minParentWeight || minParentWeight == -1)) {
                minParentWeight = vertex[i].minWeight;
                minParent = i;
            }
        }

        if(minParent == -1) break;

        AdjacencyList::EdgeList edgeList = list->getAdjList()[minParent];
        for(int i = 0; i < edgeList.size; i++){
            int tempWeight = edgeList.list[i].weight;
            if(tempWeight == -1) continue;
            int tempDest = (int)edgeList.list[i].dest;
            if (!vertex[tempDest].visited && (vertex[tempDest].minWeight > tempWeight + vertex[minParent].minWeight || vertex[tempDest].minWeight == -1)) {
                vertex[tempDest].minWeight = tempWeight + vertex[minParent].minWeight;
                vertex[tempDest].parent = minParent;
            }
        }
        vertex[minParent].visited = true;
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
void Dijkstra::printPath( const EdgeList& edgesWrap, int start, int end) {
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



