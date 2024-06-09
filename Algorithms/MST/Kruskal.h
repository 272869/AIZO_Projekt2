#ifndef AIZO_P2_KRUSKAL_H
#define AIZO_P2_KRUSKAL_H

#include "../../Utils/EdgesWrap.h"
#include "../../Graph/IncidenceMatrix.h"
#include "../../Graph/AdjacencyList.h"

class Kruskal {
    //struktura zawiera pole color, który pełni rolę identyfikatora zbioru, do którego należy dany wierzchołek.
    // Każdy wierzchołek na początku należy do unikalnego zbioru, co oznacza, że każdy wierzchołek ma inny kolor.
    //W trakcie działania algorytmu kolory są zmieniane, aby reprezentować połączenia wierzchołków.
    //Atrybut color umożliwia łatwe sprawdzenie, czy dwa wierzchołki należą do tego samego zbioru
    struct MSTVertex{
        int color;
    };
public:
    static EdgeList getMST(IncidenceMatrix* matrix);
    static EdgeList getMST(AdjacencyList* list);
};

#endif //AIZO_P2_KRUSKAL_H
