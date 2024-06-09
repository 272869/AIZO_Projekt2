#include "TransformGenerated.h"

IncidenceMatrix TransformGenerated::transformToMatrix(EdgeList *wrap) {
    IncidenceMatrix matrix(wrap->vertices, wrap->edgesNum);
    for(int i = 0; i < wrap->edgesNum; i++){
        matrix.addEdge(wrap->edges[i].start, wrap->edges[i].end, wrap->edges[i].weight, i);
    }
    return matrix;
}

AdjacencyList TransformGenerated::transformToList(EdgeList *wrap) {
    AdjacencyList list((int)wrap->vertices);
    for(int i = 0; i < wrap->edgesNum; i++){
        list.addEdge(wrap->edges[i].start, wrap->edges[i].end, wrap->edges[i].weight);
    }
    return list;
}
