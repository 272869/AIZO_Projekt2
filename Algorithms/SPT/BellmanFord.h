#ifndef AIZO_P2_BELLMANFORD_H
#define AIZO_P2_BELLMANFORD_H


#include "../../Utils/EdgesWrap.h"
#include "../../Graph/IncidenceMatrix.h"
#include "../../Graph/AdjacencyList.h"
#include "../../Utils/PathInfo.h"

class BellmanFord {
    struct SPTVertex{
        bool visited = false;
        int minWeight = -1;
        int parent = -1;
    };
public:
    static int totalCost;
    static SPTVertex* vertex;
    static EdgesWrap getSPT(IncidenceMatrix *matrix, int start);
    static EdgesWrap getSPT(AdjacencyList *list, int start);
    static int* getPath(int start, int end);
    static void printPath( EdgesWrap edgesWrap, int start, int end);
};


#endif //AIZO_P2_BELLMANFORD_H
