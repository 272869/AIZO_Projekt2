#include "TransformGenerated.h"

IncidenceMatrix TransformGenerated::transformToMatrix(EdgesWrap *wrap) {
    IncidenceMatrix matrix(wrap->vertices, wrap->edgesCount);
    for(int i = 0; i < wrap->edgesCount; i++){
        matrix.addEdge(wrap->edges[i].start, wrap->edges[i].end, wrap->edges[i].weight, i);
    }
    return matrix;
}

AdjacencyList TransformGenerated::transformToList(EdgesWrap *wrap) {
    AdjacencyList list((int)wrap->vertices);
    for(int i = 0; i < wrap->edgesCount; i++){
        list.addEdge(wrap->edges[i].start, wrap->edges[i].end, wrap->edges[i].weight);
    }
    return list;
}
