#ifndef AIZO_P2_DIJKSTRA_H
#define AIZO_P2_DIJKSTRA_H

#include "../../Graph/IncidenceMatrix.h"
#include "../../Utils/EdgesList.h"
#include "../../Graph/AdjacencyList.h"

class Dijkstra {
    struct SPTVertex{
        bool visited = false; //Informacja o tym, czy wierzchołek został odwiedzony.
        int minWeight = -1; //Minimalna waga krawędzi prowadzącej do tego wierzchołka.
        int parent = -1; //Indeks rodzica wierzchołka w drzewie SPT.
    };
public:
    static int totalCost;
    static SPTVertex* vertex;
    static EdgeList getSPT(IncidenceMatrix* matrix, int start);
    static EdgeList getSPT(AdjacencyList* list, int start);
    static void printPath(const EdgeList& edgesWrap, int start, int end);
    static int* getPath(int start, int end);
};

#endif //AIZO_P2_DIJKSTRA_H
