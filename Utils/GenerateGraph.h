#ifndef AIZO_P2_GENERATEGRAPH_H
#define AIZO_P2_GENERATEGRAPH_H

#include "EdgesWrap.h"

class GenerateGraph {
public:

private:
    static bool isExisting(EdgesWrap::Edge* list, unsigned int size, unsigned int start, unsigned int end);
    static EdgesWrap generateFor99(unsigned int vertices);
public:
    static EdgesWrap generateEdgeList(unsigned int vertices, unsigned char density);
};


#endif //AIZO_P2_GENERATEGRAPH_H
