#ifndef AIZO_P2_BELLMANFORD_H
#define AIZO_P2_BELLMANFORD_H

#include "../../Utils/EdgesList.h"
#include "../../Graph/IncidenceMatrix.h"
#include "../../Graph/AdjacencyList.h"
class BellmanFord {
    struct SPTVertex{
        bool visited = false;
        int minWeight = -1;
        int parent = -1;
    };
public:
    static int totalCost;
    static SPTVertex* vertex;
    static EdgeList getSPT(IncidenceMatrix *matrix, int start);
    static EdgeList getSPT(AdjacencyList *list, int start);
    static int* getPath(int start, int end);
    static void printPath( const EdgeList& edgesWrap, int start, int end);
};


#endif //AIZO_P2_BELLMANFORD_H
