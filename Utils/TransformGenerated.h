#ifndef AIZO_P2_TRANSFORMGENERATED_H
#define AIZO_P2_TRANSFORMGENERATED_H
#include "../Graph/IncidenceMatrix.h"
#include "../Graph/AdjacencyList.h"
#include "GenerateGraph.h"
#include "EdgesWrap.h"

class TransformGenerated {
public:
    static IncidenceMatrix transformToMatrix(EdgeList* wrap);
    static AdjacencyList transformToList(EdgeList* wrap);
};
#endif //AIZO_P2_TRANSFORMGENERATED_H
