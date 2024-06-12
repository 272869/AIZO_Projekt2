#ifndef AIZO_P2_PRIM_H
#define AIZO_P2_PRIM_H

#include "../../Utils/EdgesList.h"
#include "../../Graph/IncidenceMatrix.h"
#include "../../Graph/AdjacencyList.h"

class Prim {
    struct MSTVertex{
        bool visited = false; // Zmienna określająca, czy wierzchołek został już odwiedzony.
        int minWeight = -1; // Minimalna waga krawędzi łączącej wierzchołek z MST.
        int parent = -1; // Rodzic wierzchołka w MST.
    };
public:
    static EdgeList getMST(IncidenceMatrix* matrix);
    static EdgeList getMST(AdjacencyList* list);
};


#endif //AIZO_P2_PRIM_H
