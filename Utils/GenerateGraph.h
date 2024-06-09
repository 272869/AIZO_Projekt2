#ifndef AIZO_P2_GENERATEGRAPH_H
#define AIZO_P2_GENERATEGRAPH_H

#include "EdgesWrap.h"

class GenerateGraph {
public:

private:
    static bool isExisting(EdgeList::Edge* list, unsigned int size, unsigned int start, unsigned int end);
    static EdgeList generateFor99(unsigned int vertices);
public:
    static EdgeList generateEdgeList(unsigned int vertices, unsigned char density);
};


#endif //AIZO_P2_GENERATEGRAPH_H
