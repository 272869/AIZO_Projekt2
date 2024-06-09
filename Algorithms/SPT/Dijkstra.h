#ifndef AIZO_P2_DIJKSTRA_H
#define AIZO_P2_DIJKSTRA_H

#include "../../Graph/IncidenceMatrix.h"
#include "../../Utils/EdgesWrap.h"
#include "../../Graph/AdjacencyList.h"

class Dijkstra {
    struct SPTVertex{
        bool visited = false;
        int minWeight = -1;
        int parent = -1;
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
